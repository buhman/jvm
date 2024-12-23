#include <stdint.h>

#include "malloc.h"

struct arena {
  uint8_t * mem;
  uint32_t size;
  uint32_t ix;
};

static uint8_t class_mem[0x100000];

struct arena class_arena = {
  .mem = class_mem,
  .size = (sizeof (class_mem)),
  .ix = 0,
};

void * malloc_class_arena(uint32_t size)
{
  void * ptr = &class_arena.mem[class_arena.ix];
  class_arena.ix += size;
  return ptr;
}
