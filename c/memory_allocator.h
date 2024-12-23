#include <stdint.h>

void memory_reset_free_list();
void * memory_allocate(uint32_t size);
void memory_free(void * p);
