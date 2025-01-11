#include "object.h"
#include "printf.h"
#include "vm_instance.h"

void native_java_lang_object_getclass_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  assert(objectref != nullptr);

  struct objectref * class_objectref = vm_instance_create(vm, "java/lang/Class");
  assert(class_objectref != nullptr);
  assert(class_objectref->class_entry->instance_fields_count >= 1);

  class_objectref->oref[0] = objectref;

  operand_stack_push_ref(vm->current_frame, class_objectref);
}

void native_java_lang_object_hashcode_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  operand_stack_push_u32(vm->current_frame, (uint32_t)objectref); // objectref as integer
}
