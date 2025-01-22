#pragma once

#include <stdint.h>
#include "compat.h"

void memory_reset_free_list();
void * memory_allocate(uint32_t size);
void memory_free(void * p);
bool memory_is_allocated(void * p);
typedef void (* memory_iterate_func_t)(void * address);
void memory_iterate_allocated(memory_iterate_func_t func);
int32_t memory_count_free_memory();
int32_t memory_count_total_memory();
