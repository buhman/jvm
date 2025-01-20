#pragma once

#include <stdint.h>

#include "vm.h"

void native_jvm_internal_libcinputstream_open_1(struct vm * vm, uint32_t * args);
void native_jvm_internal_libcinputstream_close_1(struct vm * vm, uint32_t * args);
void native_jvm_internal_libcinputstream_read_1(struct vm * vm, uint32_t * args);
