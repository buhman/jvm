#pragma once

#include <stdint.h>
#include "compat.h"

void malloc_class_arena_reset();
void * malloc_class_arena(uint32_t size);
