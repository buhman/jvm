#include "class.h"
#include "printf.h"
#include "vm_instance.h"

void native_java_lang_class_getclassname_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  assert(objectref != nullptr);

  assert(objectref->oref[0] != nullptr);
  assert(objectref->oref[0]->class_entry != nullptr);
  struct class_file * class_file = objectref->oref[0]->class_entry->class_file;

  struct constant * class_constant = &class_file->constant_pool[class_file->this_class - 1];
  assert(class_constant->tag == CONSTANT_Class);

  struct constant * class_name_constant = &class_file->constant_pool[class_constant->class.name_index - 1];
  assert(class_name_constant->tag == CONSTANT_Utf8);

  struct objectref * string_objectref = vm_instance_string_from_constant(vm, class_name_constant);

  operand_stack_push_ref(vm->current_frame, string_objectref);
}
