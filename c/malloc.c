#include "assert.h"
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

void malloc_class_arena_reset()
{
  class_arena.ix = 0;
}

void * malloc_class_arena(uint32_t size)
{
  if (size == 0)
    return nullptr;

  assert((class_arena.ix & (~3)) == class_arena.ix);
  void * ptr = &class_arena.mem[class_arena.ix];
  size = (size + 3) & (~3);
  class_arena.ix += size;
  return ptr;
}
