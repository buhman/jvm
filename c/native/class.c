#include "class.h"
#include "printf.h"
#include "vm_instance.h"

void native_java_lang_class_getname_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  assert(objectref != nullptr);
  assert(objectref->oref[0] != nullptr);

  struct class_entry * class_entry = (struct class_entry *)objectref->oref[0];

  struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1];
  assert(class_constant->tag == CONSTANT_Class);

  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  assert(class_name_constant->tag == CONSTANT_Utf8);

  struct objectref * string_objectref = vm_instance_string_from_constant(vm, class_name_constant);

  operand_stack_push_ref(vm->current_frame, string_objectref);
}

void native_java_lang_class_getsuperclass_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  assert(objectref != nullptr);
  assert(objectref->oref[0] != nullptr);

  struct class_entry * class_entry = (struct class_entry *)objectref->oref[0];

  struct class_entry * super_class_entry = class_resolver_lookup_class_from_class_index(vm->class_hash_table.length,
                                                                                        vm->class_hash_table.entry,
                                                                                        class_entry,
                                                                                        class_entry->class_file->super_class);

  struct objectref * class_objectref = vm_instance_create(vm, "java/lang/Class");
  assert(class_objectref != nullptr);
  assert(class_objectref->class_entry->instance_fields_count >= 1);

  class_objectref->oref[0] = (struct objectref *)super_class_entry;

  operand_stack_push_ref(vm->current_frame, class_objectref);
}
