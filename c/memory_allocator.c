#include <stdint.h>

#include "assert.h"
#include "printf.h"

#define block_power (5UL)
#define block_size (1UL << block_power)
static uint8_t memory[0x100];
//static uint8_t memory[0x100000];
#define free_list_length ((sizeof (memory)) / block_size)
static uint8_t free_list[free_list_length];
static uint32_t free_ix;

enum allocation_state {
  ALLOCATED = 0b0001,
  START     = 0b0010,
  END       = 0b0100,
};

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

  free_list[free_ix] = START | ALLOCATED;
  for (int i = 1; i < blocks; i++) {
    free_list[free_ix + i] = ALLOCATED;
  }
  free_list[free_ix + (blocks - 1)] |= END;

  void * mem = &memory[free_ix << block_power];
  free_ix = (free_ix + blocks) & (free_list_length - 1);
  return mem;
}

void memory_free(void * p)
{
  uint8_t * buf = (uint8_t *)p;
  assert(buf >= memory);
  uint32_t address_index = buf - memory;
  assert(address_index < (sizeof (memory)));
  uint32_t free_list_index = address_index >> block_power;
  assert((free_list[free_list_index] & START) != 0);

  while ((free_list[free_list_index] & END) == 0) {
    free_list[free_list_index] = 0;
    free_list_index += 1;
  }
  free_list[free_list_index] = 0;
}

bool memory_is_allocated(void * p)
{
  uint8_t * buf = (uint8_t *)p;
  if (buf < memory)
    return false;
  uint32_t address_index = buf - memory;
  if (address_index >= (sizeof (memory)))
    return false;
  if ((address_index & (~(block_size - 1))) != address_index)
    return false;
  uint32_t free_list_index = address_index >> block_power;
  return (free_list[free_list_index] & START) != 0;
}

#if 1
void print_free_list()
{
  for (int i = 0; i < free_list_length; i++) {
    printf("%d ", free_list[i]);
  }
  printf("\n");
  for (int i = 0; i < free_list_length; i++) {
    char c = (free_ix == i) ? '^' : ' ';
    printf("%c ", c);
  }
  printf("\n");
  for (int i = 0; i < free_list_length; i++) {
    char c = memory_is_allocated((void *)((i << block_power) + memory)) ? 'X' : ' ';
    printf("%c ", c);
  }
  printf("\n");

}

int main()
{
  memory_reset_free_list();
  printf("%p\n", memory);

  void * p1 = memory_allocate(32);
  printf("p1 %p\n", p1);
  void * p2 = memory_allocate(16);
  printf("p2 %p\n", p2);
  void * p3 = memory_allocate(256);
  printf("p3 %p\n", p3);
  void * p4 = memory_allocate(90);
  printf("p4 %p\n", p4);
  print_free_list();

  memory_free(p2);
  memory_free(p1);
  void * p5 = memory_allocate(256);
  printf("p5 %p\n", p5);

  print_free_list();

  void * p6 = memory_allocate(128);
  printf("p6 %p\n", p6);

  memory_free(p4);

  print_free_list();

  void * p7 = memory_allocate(128);
  printf("p7 %p\n", p7);

  print_free_list();

  void * p8 = memory_allocate(128);
  printf("p8 %p\n", p8);
  print_free_list();

  void * p9 = memory_allocate(128);
  printf("p9 %p\n", p9);
  print_free_list();
}
#endif
