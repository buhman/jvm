#pragma once

#include <stdint.h>
#include "compat.h"
#include "vm.h"

void native_java_lang_class_getname_1(struct vm * vm, uint32_t * args);
void native_java_lang_class_getsuperclass_1(struct vm * vm, uint32_t * args);
