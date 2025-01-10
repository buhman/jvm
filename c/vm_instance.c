#include "string.h"
#include "native_types_allocate.h"
#include "vm_instance.h"

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
