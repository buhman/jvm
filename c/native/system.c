#include "system.h"

void native_java_lang_system_hashcode_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  operand_stack_push_u32(vm->current_frame, (uint32_t)objectref); // objectref as integer
}
