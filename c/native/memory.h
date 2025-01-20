#pragma once

#include <stdint.h>

#include "vm.h"

void native_jvm_internal_memory_putU4_2(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_putU2_2(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_putU1_2(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_getU4_1(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_getU2_1(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_getU1_1(struct vm * vm, uint32_t * args);

void native_jvm_internal_memory_putUnalignedU4_3(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_putUnalignedU2_3(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_getUnalignedU4_2(struct vm * vm, uint32_t * args);
void native_jvm_internal_memory_getUnalignedU2_2(struct vm * vm, uint32_t * args);

void native_jvm_internal_memory_isbigendian_0(struct vm * vm, uint32_t * args);

void native_jvm_internal_memory_allocate_1(struct vm * vm, uint32_t * args);
