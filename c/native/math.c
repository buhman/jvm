#include "math.h"

void __attribute__ ((noinline)) __attribute__ ((optimize(0)))
native_java_lang_math_sin_1(struct vm * vm, uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = __builtin_sinf(arg);
  operand_stack_push_f32(vm->current_frame, value);
}

void __attribute__ ((noinline)) __attribute__ ((optimize(0)))
native_java_lang_math_cos_1(struct vm * vm, uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = __builtin_cosf(arg);
  operand_stack_push_f32(vm->current_frame, value);
}

void native_java_lang_math_abs_1(struct vm * vm, uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = __builtin_fabsf(arg);
  operand_stack_push_f32(vm->current_frame, value);
}
