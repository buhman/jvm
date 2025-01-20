#pragma once

#include <stdint.h>

#include "vm.h"

void native_java_misc_memory_putU4_2(struct vm * vm, uint32_t * args);
void native_java_misc_memory_putU2_2(struct vm * vm, uint32_t * args);
void native_java_misc_memory_putU1_2(struct vm * vm, uint32_t * args);
void native_java_misc_memory_getU4_1(struct vm * vm, uint32_t * args);
void native_java_misc_memory_getU2_1(struct vm * vm, uint32_t * args);
void native_java_misc_memory_getU1_1(struct vm * vm, uint32_t * args);
void native_java_misc_memory_putSQ1_2(struct vm * vm, uint32_t * args);
void native_java_misc_memory_isbigendian_0(struct vm * vm, uint32_t * args);
