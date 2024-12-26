#include <stdint.h>

#include "assert.h"
#include "printf.h"

#define block_power (5UL)
#define block_size (1UL << block_power)
//static uint8_t memory[0x100];
static uint8_t memory[0x100000];
#define free_list_length ((sizeof (memory)) / block_size)
static uint8_t free_list[free_list_length];
static uint32_t free_ix;

void memory_reset_free_list()
{
  for (int i = 0; i < (sizeof (free_list)); i++) {
    free_list[i] = 0;
  }
  free_ix = 0;
}

static inline uint32_t find_contiguous_blocks(uint32_t blocks, int * zero_crossing)
{
  if (free_ix + blocks > free_list_length) {
    free_ix = 0; // non-contiguous
    (*zero_crossing) += 1;
  }

  for (uint32_t i = 0; i < blocks; i++) {
    if (free_list[free_ix + i] != 0)
      return i + 1;
  }
  return blocks;
}

void * memory_allocate(uint32_t size)
{
  assert(size != 0);

  uint32_t blocks = ((size + (block_size - 1)) & ~(block_size - 1)) >> block_power;
  int zero_crossings = 0;

  while (true) {
    uint32_t ix_offset = find_contiguous_blocks(blocks, &zero_crossings);
    if (zero_crossings > 1)
      return nullptr; // memory allocation failed
    if (ix_offset == blocks)
      break;
    free_ix = (free_ix + ix_offset) & (free_list_length - 1);
  }

  for (int i = 0; i < (blocks - 1); i++) {
    free_list[free_ix + i] = 2;
  }
  free_list[free_ix + (blocks - 1)] = 1;

  void * mem = &memory[free_ix << block_power];
  free_ix = (free_ix + blocks) & (free_list_length - 1);
  return mem;
}

void memory_free(void * p)
{
  assert(((uint8_t*)p) >= memory);
  uint32_t offset = (((uint8_t*)p) - memory) >> block_power;
  assert(free_list[offset] != 0);

  while (free_list[offset] == 2) {
    free_list[offset] = 0;
    offset += 1;
  }
  assert(free_list[offset] == 1);
  free_list[offset] = 0;
}

#if 0
int main()
{
  memory_reset_free_list();
  debugf("%p\n", memory);

  void * p1 = memory_allocate(32);
  debugf("p1 %p\n", p1);
  void * p2 = memory_allocate(16);
  debugf("p2 %p\n", p2);
  void * p3 = memory_allocate(256);
  debugf("p3 %p\n", p3);
  void * p4 = memory_allocate(90);
  debugf("p4 %p\n", p4);
  for (int i = 0; i < free_list_length; i++) { debugf("%d ", free_list[i]); }
  debugf("\n");

  memory_free(p2);
  memory_free(p1);
  void * p5 = memory_allocate(256);
  debugf("%p\n", p4);

  for (int i = 0; i < free_list_length; i++) { debugf("%d ", free_list[i]); }
  debugf("\n");

  void * p6 = memory_allocate(128);
  debugf("p5 %p\n", p5);

  memory_free(p4);

  void * p7 = memory_allocate(128);
  debugf("p6 %p\n", p6);
  void * p8 = memory_allocate(128);
  debugf("p7 %p\n", p7);
  void * p9 = memory_allocate(128);
  debugf("p8 %p\n", p8);
}
#endif
