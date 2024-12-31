#include <stdint.h>

#include "assert.h"
#include "class_file.h"
#include "hash_table.h"
#include "malloc.h"
#include "class_resolver.h"
#include "string.h"
#include "debug_class_file.h"
#include "memory_allocator.h"
#include "printf.h"
#include "field_size.h"
#include "debug.h"
#include "fatal.h"
#include "parse_type.h"

static int field_info_field_size(struct class_file * class_file, struct field_info * field_info)
{
  struct constant * field_descriptor_constant = &class_file->constant_pool[field_info->descriptor_index - 1];
  #ifdef DEBUG
  assert(field_descriptor_constant->tag == CONSTANT_Utf8);
  #endif
  return field_size(field_descriptor_constant->utf8.bytes[0]);
}

static int32_t count_superclass_instance_fields(int class_hash_table_length,
                                                struct hash_table_entry * class_hash_table,
                                                struct class_entry * class_entry)
{
  struct class_entry * subclass_entry = class_entry;

  int instance_field_count = 0;
  while (class_entry->class_file->super_class != 0) {
    class_entry = class_resolver_lookup_class_from_class_index(class_hash_table_length,
                                                               class_hash_table,
                                                               class_entry,
                                                               class_entry->class_file->super_class);
    assert(class_entry != nullptr);

    for (int i = 0; i < class_entry->class_file->fields_count; i++) {
      struct field_info * field_info = &class_entry->class_file->fields[i];
      if (!(field_info->access_flags & FIELD_ACC_STATIC)) {
        instance_field_count += 1;
      }
    }
  }

  struct constant * class_constant = &subclass_entry->class_file->constant_pool[subclass_entry->class_file->this_class - 1];
  assert(class_constant->tag == CONSTANT_Class);
  struct constant * class_name_constant = &subclass_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  assert(class_name_constant->tag == CONSTANT_Utf8);
  debugf("count_superclass_instance_fields: ");
  print_utf8_string(class_name_constant);
  debugf(": %d\n", instance_field_count);

  return instance_field_count;
}

static int add_superclass_instance_fields(int class_hash_table_length,
                                          struct hash_table_entry * class_hash_table,
                                          int fields_hash_table_length,
                                          struct hash_table_entry * fields_hash_table,
                                          struct class_entry * class_entry,
                                          int instance_index)
{
  if (class_entry->class_file->super_class != 0) {
    struct class_entry * superclass_entry = class_resolver_lookup_class_from_class_index(class_hash_table_length,
                                                                                         class_hash_table,
                                                                                         class_entry,
                                                                                         class_entry->class_file->super_class);
    assert(superclass_entry != nullptr);
    instance_index = add_superclass_instance_fields(class_hash_table_length,
                                                    class_hash_table,
                                                    fields_hash_table_length,
                                                    fields_hash_table,
                                                    superclass_entry,
                                                    instance_index);
  }

  for (int i = 0; i < class_entry->class_file->fields_count; i++) {
    struct field_info * field_info = &class_entry->class_file->fields[i];
    if (!(field_info->access_flags & FIELD_ACC_STATIC)) {
      struct field_entry * field_entry = malloc_class_arena((sizeof (struct field_entry)));
      field_entry->instance_index = instance_index;
      field_entry->field_info = field_info;

      struct constant * name_constant = &class_entry->class_file->constant_pool[field_info->name_index - 1];
      assert(name_constant->tag == CONSTANT_Utf8);
      debugf("hash table entry for instance field: ");
      print_utf8_string(name_constant);
      debugf(": %d %p\n", instance_index, field_entry);
      hash_table_add(fields_hash_table_length,
                     fields_hash_table,
                     name_constant->utf8.bytes,
                     name_constant->utf8.length,
                     (void *)field_entry);

      instance_index += field_info_field_size(class_entry->class_file, field_info);
    }
  }

  return instance_index;
}

static int32_t class_resolver_create_fields_hash_table(int class_hash_table_length,
                                                       struct hash_table_entry * class_hash_table,
                                                       struct class_entry * class_entry)
{
  int total_fields_count = class_entry->class_file->fields_count + count_superclass_instance_fields(class_hash_table_length,
                                                                                                    class_hash_table,
                                                                                                    class_entry);
  int fields_hash_table_length = hash_table_next_power_of_two(class_entry->class_file->fields_count * 2);
  uint32_t fields_hash_table_size = (sizeof (struct hash_table_entry)) * fields_hash_table_length;
  struct hash_table_entry * fields_hash_table = malloc_class_arena(fields_hash_table_size);

  int static_index = 0;

  for (int i = 0; i < class_entry->class_file->fields_count; i++) {
    struct field_info * field_info = &class_entry->class_file->fields[i];
    if (field_info->access_flags & FIELD_ACC_STATIC) {
      struct field_entry * field_entry = malloc_class_arena((sizeof (struct field_entry)));
      field_entry->static_index = static_index;
      field_entry->field_info = field_info;
      static_index += field_info_field_size(class_entry->class_file, field_info);

      struct constant * name_constant = &class_entry->class_file->constant_pool[field_info->name_index - 1];
      assert(name_constant->tag == CONSTANT_Utf8);
      debugf("hash table entry for static field: ");
      print_utf8_string(name_constant);
      debugf(": %d %p\n", static_index, field_entry);

      hash_table_add(fields_hash_table_length,
                     fields_hash_table,
                     name_constant->utf8.bytes,
                     name_constant->utf8.length,
                     (void *)field_entry);
    }
  }

  int instance_index = add_superclass_instance_fields(class_hash_table_length,
                                                      class_hash_table,
                                                      fields_hash_table_length,
                                                      fields_hash_table,
                                                      class_entry,
                                                      0);

  debugf("static_index=%d instance_index=%d total_fields_count=%d\n", static_index, instance_index, total_fields_count);

  class_entry->fields.length = fields_hash_table_length;
  class_entry->fields.entry = fields_hash_table;
  class_entry->instance_fields_count = instance_index;

  return static_index;
}

static void class_resolver_create_methods_hash_table(struct class_entry * class_entry)
{
  struct class_file * class_file = class_entry->class_file;
  int methods_hash_table_length = hash_table_next_power_of_two(class_file->methods_count * 2);
  uint32_t methods_hash_table_size = (sizeof (struct hash_table_entry)) * methods_hash_table_length;
  struct hash_table_entry * methods_hash_table = malloc_class_arena(methods_hash_table_size);
  for (int i = 0; i < class_file->methods_count; i++) {
    u2 name_index = class_file->methods[i].name_index;
    struct constant * name_constant = &class_file->constant_pool[name_index - 1];
    assert(name_constant->tag == CONSTANT_Utf8);
    u2 descriptor_index = class_file->methods[i].descriptor_index;
    struct constant * descriptor_constant = &class_file->constant_pool[descriptor_index - 1];
    assert(descriptor_constant->tag == CONSTANT_Utf8);
    debugf("hash table entry for method: ");
    debug_print__constant__method_name(name_constant, descriptor_constant);
    debugc('\n');

    hash_table_add2(methods_hash_table_length,
                    methods_hash_table,
                    name_constant->utf8.bytes,
                    name_constant->utf8.length,
                    descriptor_constant->utf8.bytes,
                    descriptor_constant->utf8.length,
                    (void *)&class_file->methods[i]);
  }

  class_entry->methods.length = methods_hash_table_length;
  class_entry->methods.entry = methods_hash_table;
}

static void class_resolver_allocate_static_fields(struct class_entry * class_entry, int32_t static_field_count)
{
  uint32_t static_fields_size = (sizeof (int32_t)) * static_field_count;
  int32_t * static_fields = malloc_class_arena(static_fields_size);

  for (int i = 0; i < static_field_count; i++) {
    static_fields[i] = 0;
  }

  class_entry->static_fields = static_fields;
}

static void class_resolver_allocate_attribute_entry(struct class_entry * class_entry)
{
  struct class_file * class_file = class_entry->class_file;
  uint32_t attribute_entry_size = (sizeof (union attribute_entry)) * class_file->constant_pool_count;
  union attribute_entry * attribute_entry = malloc_class_arena(attribute_entry_size);

  for (int i = 0; i < class_file->constant_pool_count; i++) {
    attribute_entry[i].class_entry = nullptr;
  }

  class_entry->attribute_entry = attribute_entry;
}

struct hash_table_entry * class_resolver_load_from_buffers(const uint8_t ** buffers,
                                                           int length,
                                                           int * hash_table_length)
{
  int class_hash_table_length = hash_table_next_power_of_two(hash_table_next_power_of_two(length * 2));
  uint32_t class_hash_table_size = (sizeof (struct hash_table_entry)) * class_hash_table_length;
  struct hash_table_entry * class_hash_table = malloc_class_arena(class_hash_table_size);
  uint32_t class_entry_size = (sizeof (struct class_entry)) * length;
  struct class_entry * class_entry = malloc_class_arena(class_entry_size);

  // populate class_hash_table first, to allow for superclass lookups
  for (int i = 0; i < length; i++) {
    struct class_file * class_file = class_file_parse(buffers[i]);

    assert(class_file->magic == 0xcafebabe);

    class_entry[i].class_file = class_file;
    class_entry[i].initialization_state = CLASS_UNINITIALIZED;

    struct constant * class_constant = &class_file->constant_pool[class_file->this_class - 1];
    assert(class_constant->tag == CONSTANT_Class);
    struct constant * class_name_constant = &class_file->constant_pool[class_constant->class.name_index - 1];
    assert(class_name_constant->tag == CONSTANT_Utf8);
    debugf("hash table entry for class: ");
    print_utf8_string(class_name_constant);
    debugf("\n");

    hash_table_add(class_hash_table_length,
                   class_hash_table,
                   class_name_constant->utf8.bytes,
                   class_name_constant->utf8.length,
                   &class_entry[i]);

    // make hash table for methods
    class_resolver_create_methods_hash_table(&class_entry[i]);

    // allocate attribute_entry
    class_resolver_allocate_attribute_entry(&class_entry[i]);
  };

  // these functions may reference class_hash_table for superclass lookups
  for (int i = 0; i < length; i++) {
    // make hash table for fields
    int32_t static_field_count = class_resolver_create_fields_hash_table(class_hash_table_length,
                                                                         class_hash_table,
                                                                         &class_entry[i]);

    // allocate static fields
    class_resolver_allocate_static_fields(&class_entry[i], static_field_count);
  }

  *hash_table_length = class_hash_table_length;

  return class_hash_table;
}

struct class_entry * class_resolver_lookup_class(int class_hash_table_length,
                                                 struct hash_table_entry * class_hash_table,
                                                 const uint8_t * class_name,
                                                 int class_name_length)
{
  debugf("class_resolver_lookup_class: ");
  for (int i = 0; i < class_name_length; i++) { debugc(class_name[i]); }
  debugc('\n');

  struct hash_table_entry * e = hash_table_find(class_hash_table_length,
                                                class_hash_table,
                                                class_name,
                                                class_name_length);
  if (e == nullptr) {
    fatal_print__class_lookup_failed__from_string(class_name, class_name_length);
    assert(e != nullptr);
  }

  return (struct class_entry *)e->value;
}

struct class_entry * class_resolver_lookup_class_from_class_index(int class_hash_table_length,
                                                                  struct hash_table_entry * class_hash_table,
                                                                  struct class_entry * class_entry,
                                                                  int32_t class_index)
{
  if (class_entry->attribute_entry[class_index - 1].class_entry != nullptr) {
    debugf("class_resolver_lookup_class_from_class_index %d: [cached]\n", class_index);
    return class_entry->attribute_entry[class_index - 1].class_entry;
  }

  struct constant * class_constant = &class_entry->class_file->constant_pool[class_index - 1];
  assert(class_constant->tag == CONSTANT_Class);
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  assert(class_name_constant->tag == CONSTANT_Utf8);

  struct parse_type_ret parse_type_ret = parse_type(class_name_constant->utf8.bytes,
                                                    class_name_constant->utf8.length);


  struct class_entry * _class_entry = class_resolver_lookup_class(class_hash_table_length,
                                                                  class_hash_table,
                                                                  parse_type_ret.bytes,
                                                                  parse_type_ret.length);
  if (_class_entry != nullptr) {
    // cache the result
    class_entry->attribute_entry[class_index - 1].class_entry = _class_entry;
  }

  return _class_entry;
}

struct field_entry * class_resolver_lookup_field(int fields_hash_table_length,
                                                 struct hash_table_entry * fields_hash_table,
                                                 const uint8_t * field_name,
                                                 int field_name_length)
{
  debugf("class_resolver_lookup_field: ");
  for (int i = 0; i < field_name_length; i++) { debugc(field_name[i]); }
  debugc('\n');

  struct hash_table_entry * e = hash_table_find(fields_hash_table_length,
                                                fields_hash_table,
                                                field_name,
                                                field_name_length);
  assert(e != nullptr);
  debugf("%p\n", e->value);

  return (struct field_entry *)e->value;
}

struct field_entry * class_resolver_lookup_field_from_fieldref_index(int fields_hash_table_length,
                                                                     struct hash_table_entry * fields_hash_table,
                                                                     struct class_entry * class_entry,
                                                                     int fieldref_index)
{
  if (class_entry->attribute_entry[fieldref_index - 1].field_entry != nullptr) {
    debugf("class_resolver_lookup_field_from_fieldref_index %d: [cached]\n", fieldref_index);
    return class_entry->attribute_entry[fieldref_index - 1].field_entry;
  }

  struct constant * fieldref_constant = &class_entry->class_file->constant_pool[fieldref_index - 1];
  #ifdef DEBUG
  assert(fieldref_constant->tag == CONSTANT_Fieldref);
  #endif
  struct constant * nameandtype_constant = &class_entry->class_file->constant_pool[fieldref_constant->fieldref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  struct constant * field_name_constant = &class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  #ifdef DEBUG
  assert(field_name_constant->tag == CONSTANT_Utf8);
  #endif

  struct field_entry * field_entry = class_resolver_lookup_field(fields_hash_table_length,
                                                                 fields_hash_table,
                                                                 field_name_constant->utf8.bytes,
                                                                 field_name_constant->utf8.length);

  // cache the result
  class_entry->attribute_entry[fieldref_index - 1].field_entry = field_entry;

  return field_entry;
}

struct method_info * class_resolver_lookup_method(int methods_hash_table_length,
                                                  struct hash_table_entry * methods_hash_table,
                                                  const uint8_t * method_name,
                                                  int method_name_length,
                                                  const uint8_t * method_descriptor,
                                                  int method_descriptor_length)
{
  debugf("class_resolver_lookup_method: ");
  for (int i = 0; i < method_name_length; i++) { debugc(method_name[i]); }
  debugc(' ');
  for (int i = 0; i < method_descriptor_length; i++) { debugc(method_descriptor[i]); }
  debugc('\n');

  struct hash_table_entry * e = hash_table_find2(methods_hash_table_length,
                                                 methods_hash_table,
                                                 method_name,
                                                 method_name_length,
                                                 method_descriptor,
                                                 method_descriptor_length);
  if (e == nullptr)
    return nullptr;

  return (struct method_info *)e->value;
}

struct method_entry class_resolver_lookup_method_from_interfacemethodref_index(int class_hash_table_length,
                                                                               struct hash_table_entry * class_hash_table,
                                                                               int32_t interfacemethodref_index,
                                                                               struct class_entry * objectref_class_entry,
                                                                               struct class_entry * origin_class_entry)
{
  struct constant * interfacemethodref_constant = &origin_class_entry->class_file->constant_pool[interfacemethodref_index - 1];
  assert(interfacemethodref_constant->tag == CONSTANT_InterfaceMethodref || interfacemethodref_constant->tag == CONSTANT_Methodref);
  struct constant * nameandtype_constant = &origin_class_entry->class_file->constant_pool[interfacemethodref_constant->interfacemethodref.name_and_type_index - 1];
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  struct constant * method_name_constant = &origin_class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  assert(method_name_constant->tag == CONSTANT_Utf8);
  struct constant * method_descriptor_constant = &origin_class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  assert(method_descriptor_constant->tag == CONSTANT_Utf8);

  struct class_entry * class_entry = objectref_class_entry;

  while (true) {
    struct method_info * method_info = class_resolver_lookup_method(class_entry->methods.length,
                                                                    class_entry->methods.entry,
                                                                    method_name_constant->utf8.bytes,
                                                                    method_name_constant->utf8.length,
                                                                    method_descriptor_constant->utf8.bytes,
                                                                    method_descriptor_constant->utf8.length);
    if (method_info != nullptr) {
      debugf("method resolved:\n");
      debugf("  class: ");
      debug_print__class_entry__class_name(class_entry);
      debugf("\n  method: ");
      debug_print__method_info__method_name(class_entry, method_info);
      debugc('\n');

      return (struct method_entry){
        .class_entry = class_entry,
        .method_info = method_info
      };
    }

    if (class_entry->class_file->super_class == 0)
      break;

    struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->super_class - 1];
    assert(class_constant->tag == CONSTANT_Class);
    struct constant * class_name_constant =  &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
    assert(class_name_constant->tag == CONSTANT_Utf8);
    print_utf8_string(class_name_constant);
    debugf("\n");

    // lookup the method from the superclass
    class_entry = class_resolver_lookup_class_from_class_index(class_hash_table_length,
                                                               class_hash_table,
                                                               class_entry,
                                                               class_entry->class_file->super_class);
    assert(class_entry != nullptr);
  }

  assert(!"interfacemethodref method does not exist");
}

struct method_entry * class_resolver_lookup_method_from_methodref_index(int class_hash_table_length,
                                                                        struct hash_table_entry * class_hash_table,
                                                                        int32_t methodref_index,
                                                                        struct class_entry * origin_class_entry)
{
  if (origin_class_entry->attribute_entry[methodref_index - 1].method_entry != nullptr) {
    debugf("class_resolver_lookup_method_from_methodref_index %d: [cached]\n", methodref_index);
    return origin_class_entry->attribute_entry[methodref_index - 1].method_entry;
  }

  struct constant * methodref_constant = &origin_class_entry->class_file->constant_pool[methodref_index - 1];
  assert(methodref_constant->tag == CONSTANT_Methodref);
  struct constant * nameandtype_constant = &origin_class_entry->class_file->constant_pool[methodref_constant->methodref.name_and_type_index - 1];
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  struct constant * method_name_constant = &origin_class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  assert(method_name_constant->tag == CONSTANT_Utf8);
  struct constant * method_descriptor_constant = &origin_class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  assert(method_descriptor_constant->tag == CONSTANT_Utf8);

  struct class_entry * class_entry = class_resolver_lookup_class_from_class_index(class_hash_table_length,
                                                                                  class_hash_table,
                                                                                  origin_class_entry,
                                                                                  methodref_constant->methodref.class_index);

  while (true) {
    struct method_info * method_info = class_resolver_lookup_method(class_entry->methods.length,
                                                                    class_entry->methods.entry,
                                                                    method_name_constant->utf8.bytes,
                                                                    method_name_constant->utf8.length,
                                                                    method_descriptor_constant->utf8.bytes,
                                                                    method_descriptor_constant->utf8.length);
    if (method_info != nullptr) {
      // cache the result
      debugf("method resolved:\n");
      debugf("  class: ");
      debug_print__class_entry__class_name(class_entry);
      debugf("\n  method: ");
      debug_print__method_info__method_name(class_entry, method_info);
      debugc('\n');

      struct method_entry * method_entry = malloc_class_arena((sizeof (struct method_entry)));
      method_entry->class_entry = class_entry;
      method_entry->method_info = method_info;
      origin_class_entry->attribute_entry[methodref_index - 1].method_entry = method_entry;
      return method_entry;
    }

    if (class_entry->class_file->super_class == 0)
      break;

    struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->super_class - 1];
    assert(class_constant->tag == CONSTANT_Class);
    struct constant * class_name_constant =  &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
    assert(class_name_constant->tag == CONSTANT_Utf8);
    print_utf8_string(class_name_constant);
    debugf("\n");

    // lookup the method from the superclass
    class_entry = class_resolver_lookup_class_from_class_index(class_hash_table_length,
                                                               class_hash_table,
                                                               class_entry,
                                                               class_entry->class_file->super_class);
    assert(class_entry != nullptr);
  }

  assert(!"methodref method does not exist");
}

int32_t * class_resolver_lookup_string(int class_hash_table_length,
                                       struct hash_table_entry * class_hash_table,
                                       struct class_entry * class_entry,
                                       const int string_index)
{
  debugf("class_resolver_lookup_string: %d\n", string_index);
  if (class_entry->attribute_entry[string_index - 1].string_objectref != nullptr) {
    debugf("class_resolver_lookup_string: [cached]\n");
    return class_entry->attribute_entry[string_index - 1].string_objectref;
  }

  struct constant * utf8_constant = &class_entry->class_file->constant_pool[string_index - 1];
  assert(utf8_constant->tag == CONSTANT_Utf8);

  struct class_entry * string_class_entry = class_resolver_lookup_class(class_hash_table_length,
                                                                        class_hash_table,
                                                                        (const uint8_t *)"java/lang/String",
                                                                        16);

  int32_t size = utf8_constant->utf8.length + 4;
  int32_t * arrayref = memory_allocate(size);
  assert(arrayref != nullptr);
  arrayref[0] = utf8_constant->utf8.length;
  uint8_t * bytearray = (uint8_t *)&arrayref[1];
  for (int i = 0; i < utf8_constant->utf8.length; i++)
    bytearray[i] = utf8_constant->utf8.bytes[i];

  assert(string_class_entry != nullptr);
  int32_t * objectref = memory_allocate(4 + 4);
  assert(objectref != nullptr);
  objectref[0] = (int32_t)string_class_entry;
  objectref[1] = (int32_t)arrayref;

  // cache the result
  class_entry->attribute_entry[string_index - 1].string_objectref = objectref;

  return objectref;
}
