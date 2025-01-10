#include "native_types.h"
#include "memory.h"

void native_java_misc_memory_putU4_2(struct vm * vm, uint32_t * args)
{
  uint32_t * address = (uint32_t *)args[0];
  uint32_t value = args[1];
  *address = value;
}

void native_java_misc_memory_putU2_2(struct vm * vm, uint32_t * args)
{
  uint16_t * address = (uint16_t *)args[0];
  uint16_t value = args[1];
  *address = value;
}

void native_java_misc_memory_putU1_2(struct vm * vm, uint32_t * args)
{
  uint8_t * address = (uint8_t *)args[0];
  uint8_t value = args[1];
  *address = value;
}

void native_java_misc_memory_getU4_1(struct vm * vm, uint32_t * args)
{
  uint32_t * address = (uint32_t *)args[0];
  uint32_t value = *address;
  operand_stack_push_u32(vm->current_frame, value);
}

void native_java_misc_memory_getU2_1(struct vm * vm, uint32_t * args)
{
  uint16_t * address = (uint16_t *)args[0];
  uint16_t value = *address;
  operand_stack_push_u32(vm->current_frame, value);
}

void native_java_misc_memory_getU1_1(struct vm * vm, uint32_t * args)
{
  uint8_t * address = (uint8_t *)args[0];
  uint8_t value = *address;
  operand_stack_push_u32(vm->current_frame, value);
}

extern uint32_t store_queue[0x4000000] __asm("store_queue");

void native_java_misc_memory_putSQ1_2(struct vm * vm, uint32_t * args)
{
  #if defined(__dreamcast__)
  struct objectref * objectref = (struct objectref *)args[0];
  uint32_t address = (uint32_t)args[1];
  store_queue[0] = objectref->u32[0];
  store_queue[1] = objectref->u32[1];
  store_queue[2] = objectref->u32[2];
  store_queue[3] = objectref->u32[3];
  store_queue[4] = objectref->u32[4];
  store_queue[5] = objectref->u32[5];
  store_queue[6] = objectref->u32[6];
  store_queue[7] = objectref->u32[7];

  *((uint32_t*)0xff000038) = ((address >> 26) & 0b111) << 2;

  __asm__ volatile ("pref @%0"
                    :                       // output
                    : "r" (&store_queue[0]) // input
                    : "memory");
  #endif
}

void native_java_misc_memory_isbigendian_0(struct vm * vm, uint32_t * args)
{
  uint32_t value = (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__);
  operand_stack_push_u32(vm->current_frame, value);
}
