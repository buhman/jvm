#include "string.h"
#include "native_types_allocate.h"
#include "vm_instance.h"
#include "class_resolver.h"

struct objectref * vm_instance_create(struct vm * vm, const char * class_name)
{
  struct class_entry * class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                                                 vm->class_hash_table.entry,
                                                                 (const uint8_t *)class_name,
                                                                 string_length(class_name));
  assert(class_entry != nullptr);

  struct objectref * objectref = obj_allocate(vm, class_entry->instance_fields_count);
  if (objectref != nullptr) {
    objectref->class_entry = class_entry;

    for (int i = 0; i < class_entry->instance_fields_count; i++) {
      objectref->oref[i] = nullptr;
    }
  }

  return objectref;
}

struct objectref * vm_instance_string_from_constant(struct vm * vm, struct constant * constant)
{
  int32_t count = constant->utf8.length;
  struct arrayref * arrayref = prim_array_allocate(vm, 2, count);
  assert(arrayref != nullptr);
  arrayref->class_entry = nullptr; // byte[]
  arrayref->length = constant->utf8.length;
  for (int i = 0; i < constant->utf8.length; i++) {
    arrayref->u16[i] = constant->utf8.bytes[i];
  }

  struct objectref * objectref = vm_instance_create(vm, "java/lang/String");
  assert(objectref != nullptr);
  assert(objectref->class_entry->instance_fields_count >= 1);
  objectref->aref[0] = arrayref;

  return objectref;
}
