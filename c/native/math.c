#include "math.h"

float __attribute__ ((noinline)) cosf(float f)
{
    return __builtin_cosf(f);
}

float __attribute__ ((noinline)) sinf(float f)
{
    return __builtin_sinf(f);
}

void
native_java_lang_math_sin_1(struct vm * vm, uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = sinf(arg);
  operand_stack_push_f32(vm->current_frame, value);
}

void
native_java_lang_math_cos_1(struct vm * vm, uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = cosf(arg);
  operand_stack_push_f32(vm->current_frame, value);
}

void native_java_lang_math_abs_1(struct vm * vm, uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = __builtin_fabsf(arg);
  operand_stack_push_f32(vm->current_frame, value);
}
