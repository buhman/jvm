#include "memory.h"
#include "memory_allocator.h"

void native_jvm_internal_memory_putU4_2(struct vm * vm, uint32_t * args)
{
  uint32_t * address = (uint32_t *)args[0];
  uint32_t value = args[1];
  *address = value;
}

void native_jvm_internal_memory_putU2_2(struct vm * vm, uint32_t * args)
{
  uint16_t * address = (uint16_t *)args[0];
  uint16_t value = args[1];
  *address = value;
}

void native_jvm_internal_memory_putU1_2(struct vm * vm, uint32_t * args)
{
  uint8_t * address = (uint8_t *)args[0];
  uint8_t value = args[1];
  *address = value;
}

void native_jvm_internal_memory_getU4_1(struct vm * vm, uint32_t * args)
{
  uint32_t * address = (uint32_t *)args[0];
  uint32_t value = *address;
  operand_stack_push_u32(vm->current_frame, value);
}

void native_jvm_internal_memory_getU2_1(struct vm * vm, uint32_t * args)
{
  uint16_t * address = (uint16_t *)args[0];
  uint16_t value = *address;
  operand_stack_push_u32(vm->current_frame, value);
}

void native_jvm_internal_memory_getU1_1(struct vm * vm, uint32_t * args)
{
  uint8_t * address = (uint8_t *)args[0];
  uint8_t value = *address;
  operand_stack_push_u32(vm->current_frame, value);
}

static inline void unaligned_store_u4(uint32_t address, uint32_t value, bool big_endian)
{
  if ((address & 3) == 0) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    if (big_endian)
      *((uint32_t *)address) = value;
    else
      *((uint32_t *)address) = __builtin_bswap32(value);
#else // LITTLE_ENDIAN
    if (!big_endian)
      *((uint32_t *)address) = value;
    else
      *((uint32_t *)address) = __builtin_bswap32(value);
#endif
  } else {
    if (big_endian) {
      ((uint8_t *)address)[0] = (uint8_t)(value >> 24);
      ((uint8_t *)address)[1] = (uint8_t)(value >> 16);
      ((uint8_t *)address)[2] = (uint8_t)(value >> 8);
      ((uint8_t *)address)[3] = (uint8_t)(value >> 0);
    } else {
      ((uint8_t *)address)[0] = (uint8_t)(value >> 0);
      ((uint8_t *)address)[1] = (uint8_t)(value >> 8);
      ((uint8_t *)address)[2] = (uint8_t)(value >> 16);
      ((uint8_t *)address)[3] = (uint8_t)(value >> 24);
    }
  }
}

static inline void unaligned_store_u2(uint32_t address, uint32_t value, bool big_endian)
{
  if ((address & 1) == 0) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    if (big_endian)
      *((uint16_t *)address) = value;
    else
      *((uint16_t *)address) = __builtin_bswap16(value);
#else // LITTLE_ENDIAN
    if (!big_endian)
      *((uint16_t *)address) = value;
    else
      *((uint16_t *)address) = __builtin_bswap16(value);
#endif
  } else {
    if (big_endian) {
      ((uint8_t *)address)[0] = (uint8_t)(value >> 8);
      ((uint8_t *)address)[1] = (uint8_t)(value >> 0);
    } else {
      ((uint8_t *)address)[0] = (uint8_t)(value >> 0);
      ((uint8_t *)address)[1] = (uint8_t)(value >> 8);
    }
  }
}

void native_jvm_internal_memory_putUnalignedU4_3(struct vm * vm, uint32_t * args)
{
  uint32_t address = (uint32_t)args[0];
  uint32_t value = args[1];
  bool big_endian = args[2];

  unaligned_store_u4(address, value, big_endian);
}

void native_jvm_internal_memory_putUnalignedU2_3(struct vm * vm, uint32_t * args)
{
  uint32_t address = (uint32_t)args[0];
  uint32_t value = args[1];
  bool big_endian = args[2];

  unaligned_store_u2(address, value, big_endian);
}

static inline uint32_t unaligned_load_u4(uint32_t address, bool big_endian)
{
  uint32_t value;
  if ((address & 3) == 0) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    if (big_endian)
      value = *((uint32_t *)address);
    else
      value = __builtin_bswap32(*((uint32_t *)address));
#else // LITTLE_ENDIAN
    if (!big_endian)
      value = *((uint32_t *)address);
    else
      value = __builtin_bswap32(*((uint32_t *)address));
#endif
  } else {
    if (big_endian) {
      value =
        ((((uint8_t *)address)[0] << 24) |
         (((uint8_t *)address)[1] << 16) |
         (((uint8_t *)address)[2] << 8 ) |
         (((uint8_t *)address)[3] << 0 ));
    } else {
      value =
        ((((uint8_t *)address)[0] << 0 ) |
         (((uint8_t *)address)[1] << 8 ) |
         (((uint8_t *)address)[2] << 16) |
         (((uint8_t *)address)[3] << 24));
    }
  }
  return value;
}

static inline uint32_t unaligned_load_u2(uint32_t address, bool big_endian)
{
  uint32_t value;
  if ((address & 1) == 0) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    if (big_endian)
      value = *((uint32_t *)address);
    else
      value = __builtin_bswap32(*((uint32_t *)address));
#else // LITTLE_ENDIAN
    if (!big_endian)
      value = *((uint32_t *)address);
    else
      value = __builtin_bswap32(*((uint32_t *)address));
#endif
  } else {
    if (big_endian) {
      value =
        ((((uint8_t *)address)[0] << 8 ) |
         (((uint8_t *)address)[1] << 0 ));
    } else {
      value =
        ((((uint8_t *)address)[0] << 0 ) |
         (((uint8_t *)address)[1] << 8 ));
    }
  }
  return value;
}

void native_jvm_internal_memory_getUnalignedU4_2(struct vm * vm, uint32_t * args)
{
  uint32_t address = (uint32_t)args[0];
  bool big_endian = args[1];

  uint32_t value = unaligned_load_u4(address, big_endian);

  operand_stack_push_u32(vm->current_frame, value);
}

void native_jvm_internal_memory_getUnalignedU2_2(struct vm * vm, uint32_t * args)
{
  uint32_t address = (uint32_t)args[0];
  bool big_endian = args[1];

  uint32_t value = unaligned_load_u2(address, big_endian);

  operand_stack_push_u32(vm->current_frame, value);
}

void native_jvm_internal_memory_isbigendian_0(struct vm * vm, uint32_t * args)
{
  uint32_t value = (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__);
  operand_stack_push_u32(vm->current_frame, value);
}

void native_jvm_internal_memory_allocate_1(struct vm * vm, uint32_t * args)
{
  uint32_t capacity = (uint32_t)args[0];

  void * address = memory_allocate(capacity);

  operand_stack_push_u32(vm->current_frame, (uint32_t)address);
}
