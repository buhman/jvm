#pragma once

#include <stdint.h>

#include "vm.h"

void native_java_lang_math_sin_1(struct vm * vm, uint32_t * args);
void native_java_lang_math_cos_1(struct vm * vm, uint32_t * args);
void native_java_lang_math_abs_1(struct vm * vm, uint32_t * args);
