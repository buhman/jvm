#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "class_file.h"
#include "file.h"
#include "hash_table.h"
#include "malloc.h"
#include "class_resolver.h"
#include "string.h"
#include "debug_class_file.h"
#include "memory_allocator.h"

static void class_resolver_create_interfaces_hash_table(struct class_entry * class_entry)
{
  /*
  struct class_file * class_file = class_entry->class_file;

  uint32_t interfaces_hash_table_size = (sizeof (struct hash_table_entry)) * class_file->interfaces_count * 3 / 2;
  struct hash_table_entry * interfaces_hash_table = malloc_class_arena(interfaces_hash_table_size);
  for (int i = 0; i < class_file->interfaces_count; i++) {

  }
  */
}

static int field_size(struct class_file * class_file, struct field_info * field_info)
{
  struct constant * field_descriptor_constant = &class_file->constant_pool[field_info->descriptor_index - 1];
  #ifdef DEBUG
  assert(field_descriptor_constant->tag == CONSTANT_Utf8);
  #endif

  switch (field_descriptor_constant->utf8.bytes[0]) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    return 1;
  case 'D': [[fallthrough]];
  case 'J':
    return 2;
  default:
    assert(false);
  }
}

static int32_t class_resolver_create_fields_hash_table(struct class_entry * class_entry)
{
  struct class_file * class_file = class_entry->class_file;
  int fields_hash_table_length = class_file->fields_count * 2;
  uint32_t fields_hash_table_size = (sizeof (struct hash_table_entry)) * fields_hash_table_length;
  struct hash_table_entry * fields_hash_table = malloc_class_arena(fields_hash_table_size);
  uint32_t field_entry_size = (sizeof (struct field_entry)) * class_file->fields_count;
  struct field_entry * field_entry = malloc_class_arena(field_entry_size);

  int32_t static_index = 0;
  int32_t instance_index = 0;

  for (int i = 0; i < class_file->fields_count; i++) {
    u2 name_index = class_file->fields[i].name_index;
    struct constant * name_constant = &class_file->constant_pool[name_index - 1];
    assert(name_constant->tag == CONSTANT_Utf8);
    printf("hash table entry for field: ");
    print_utf8_string(name_constant);
    printf("\n");

    struct field_info * field_info = &class_file->fields[i];

    if (field_info->access_flags & FIELD_ACC_STATIC) {
      field_entry[i].static_index = static_index;
      static_index += field_size(class_file, field_info);
    } else {
      field_entry[i].instance_index = instance_index;
      instance_index += field_size(class_file, field_info);
    }
    field_entry[i].field_info = field_info;

    hash_table_add(fields_hash_table_length,
                   fields_hash_table,
                   name_constant->utf8.bytes,
                   name_constant->utf8.length,
                   (void *)&field_entry[i]);
  }

  class_entry->fields.length = fields_hash_table_length;
  class_entry->fields.entry = fields_hash_table;

  return static_index;
}

static void class_resolver_create_methods_hash_table(struct class_entry * class_entry)
{
  struct class_file * class_file = class_entry->class_file;
  int methods_hash_table_length = class_file->methods_count * 2;
  uint32_t methods_hash_table_size = (sizeof (struct hash_table_entry)) * methods_hash_table_length;
  struct hash_table_entry * methods_hash_table = malloc_class_arena(methods_hash_table_size);
  for (int i = 0; i < class_file->methods_count; i++) {
    u2 name_index = class_file->methods[i].name_index;
    struct constant * name_constant = &class_file->constant_pool[name_index - 1];
    assert(name_constant->tag == CONSTANT_Utf8);
    u2 descriptor_index = class_file->methods[i].descriptor_index;
    struct constant * descriptor_constant = &class_file->constant_pool[descriptor_index - 1];
    assert(descriptor_constant->tag == CONSTANT_Utf8);
    printf("hash table entry for method: ");
    print_utf8_string(name_constant);
    printf("\n");

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

struct hash_table_entry * class_resolver_load_from_filenames(const char * filenames[], int length, int * hash_table_length)
{
  int class_hash_table_length = length * 2;
  uint32_t class_hash_table_size = (sizeof (struct hash_table_entry)) * class_hash_table_length;
  struct hash_table_entry * class_hash_table = malloc_class_arena(class_hash_table_size);
  uint32_t class_entry_size = (sizeof (struct class_entry)) * length;
  struct class_entry * class_entry = malloc_class_arena(class_entry_size);

  for (int i = 0; i < length; i++) {
    uint32_t filename_length = string_length(filenames[i]);
    const char * suffix = ".class";
    uint32_t suffix_length = string_length(suffix);
    const char * filename_suffix = &filenames[i][filename_length - suffix_length];
    if (filename_length <= suffix_length || !string_equal(suffix, filename_suffix)) {
      printf("invalid class filename: %s\n", filenames[i]);
      continue;
    }
    uint32_t class_name_length = filename_length - suffix_length;

    printf("load class: %s\n", filenames[i]);

    uint8_t * buf = file_read(filenames[i]);
    struct class_file * class_file = class_file_parse(buf);
    free(buf);

    assert(class_file->magic == 0xcafebabe);

    class_entry[i].class_file = class_file;
    class_entry[i].initialization_state = CLASS_UNINITIALIZED;

    hash_table_add(class_hash_table_length,
                   class_hash_table,
                   (const uint8_t *)filenames[i],
                   class_name_length,
                   &class_entry[i]);

    // make hash table for interfaces
    class_resolver_create_interfaces_hash_table(&class_entry[i]);

    // make hash table for fields
    int32_t static_field_count = class_resolver_create_fields_hash_table(&class_entry[i]);

    // make hash table for methods
    class_resolver_create_methods_hash_table(&class_entry[i]);

    // allocate static fields
    class_resolver_allocate_static_fields(&class_entry[i], static_field_count);

    // allocate attribute_entry
    class_resolver_allocate_attribute_entry(&class_entry[i]);
  };

  *hash_table_length = class_hash_table_length;

  return class_hash_table;
}

struct class_entry * class_resolver_lookup_class(int class_hash_table_length,
                                                 struct hash_table_entry * class_hash_table,
                                                 const uint8_t * class_name,
                                                 int class_name_length)
{
  printf("class_resolver_lookup_class: ");
  for (int i = 0; i < class_name_length; i++) { fputc(class_name[i], stdout); }
  fputc('\n', stdout);

  struct hash_table_entry * e = hash_table_find(class_hash_table_length,
                                                class_hash_table,
                                                class_name,
                                                class_name_length);
  assert(e != nullptr);

  return (struct class_entry *)e->value;
}

struct class_entry * class_resolver_lookup_class_from_class_index(int class_hash_table_length,
                                                                  struct hash_table_entry * class_hash_table,
                                                                  struct class_entry * class_entry,
                                                                  int32_t class_index)
{
  if (class_entry->attribute_entry[class_index - 1].class_entry != nullptr) {
    printf("class_resolver_lookup_class_from_class_index %d: [cached]\n", class_index);
    return class_entry->attribute_entry[class_index - 1].class_entry;
  }

  struct constant * class_constant = &class_entry->class_file->constant_pool[class_index - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif

  struct class_entry * _class_entry = class_resolver_lookup_class(class_hash_table_length,
                                                                  class_hash_table,
                                                                  class_name_constant->utf8.bytes,
                                                                  class_name_constant->utf8.length);

  // cache the result
  class_entry->attribute_entry[class_index - 1].class_entry = _class_entry;

  return _class_entry;
}

struct field_entry * class_resolver_lookup_field(int fields_hash_table_length,
                                                 struct hash_table_entry * fields_hash_table,
                                                 const uint8_t * field_name,
                                                 int field_name_length)
{
  printf("class_resolver_lookup_field: ");
  for (int i = 0; i < field_name_length; i++) { fputc(field_name[i], stdout); }
  fputc('\n', stdout);

  struct hash_table_entry * e = hash_table_find(fields_hash_table_length,
                                                fields_hash_table,
                                                field_name,
                                                field_name_length);
  assert(e != nullptr);

  return (struct field_entry *)e->value;
}

struct field_entry * class_resolver_lookup_field_from_fieldref_index(int fields_hash_table_length,
                                                                     struct hash_table_entry * fields_hash_table,
                                                                     struct class_entry * class_entry,
                                                                     int fieldref_index)
{
  if (class_entry->attribute_entry[fieldref_index - 1].field_entry != nullptr) {
    printf("class_resolver_lookup_method_from_fieldref_index %d: [cached]\n", fieldref_index);
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
  printf("class_resolver_lookup_method: ");
  for (int i = 0; i < method_name_length; i++) { fputc(method_name[i], stdout); }
  fputc(' ', stdout);
  for (int i = 0; i < method_descriptor_length; i++) { fputc(method_descriptor[i], stdout); }
  fputc('\n', stdout);

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

struct method_info * class_resolver_lookup_method_from_methodref_index(int methods_hash_table_length,
                                                                       struct hash_table_entry * methods_hash_table,
                                                                       struct class_entry * class_entry,
                                                                       int methodref_index)
{
  if (class_entry->attribute_entry[methodref_index - 1].method_info != nullptr) {
    printf("class_resolver_lookup_method_from_methodref_index %d: [cached]\n", methodref_index);
    return class_entry->attribute_entry[methodref_index - 1].method_info;
  }

  struct constant * methodref_constant = &class_entry->class_file->constant_pool[methodref_index - 1];
  #ifdef DEBUG
  assert(methodref_constant->tag == CONSTANT_Methodref);
  #endif
  struct constant * nameandtype_constant = &class_entry->class_file->constant_pool[methodref_constant->methodref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  struct constant * method_name_constant = &class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  #ifdef DEBUG
  assert(method_name_constant->tag == CONSTANT_Utf8);
  #endif
  struct constant * method_descriptor_constant = &class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  #ifdef DEBUG
  assert(method_descriptor_constant->tag == CONSTANT_Utf8);
  #endif

  struct method_info * method_info = class_resolver_lookup_method(methods_hash_table_length,
                                                                  methods_hash_table,
                                                                  method_name_constant->utf8.bytes,
                                                                  method_name_constant->utf8.length,
                                                                  method_descriptor_constant->utf8.bytes,
                                                                  method_descriptor_constant->utf8.length);

  // cache the result
  class_entry->attribute_entry[methodref_index - 1].method_info = method_info;

  return method_info;
}

int32_t * class_resolver_lookup_string(int class_hash_table_length,
                                       struct hash_table_entry * class_hash_table,
                                       struct class_entry * class_entry,
                                       const int string_index)
{
  printf("class_resolver_lookup_string: %d\n", string_index);
  if (class_entry->attribute_entry[string_index - 1].string_objectref != nullptr) {
    printf("class_resolver_lookup_string: [cached]\n");
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
