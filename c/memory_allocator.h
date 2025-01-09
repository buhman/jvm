#pragma once

#include <stdint.h>

void memory_reset_free_list();
void * memory_allocate(uint32_t size);
void memory_free(void * p);
bool memory_is_allocated(void * p);
typedef void (* memory_iterate_func_t)(void * address);
void memory_iterate_allocated(memory_iterate_func_t func);
