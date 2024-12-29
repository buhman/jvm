#include "native.h"
#include "printf.h"

void native_java_io_printstream_write(uint32_t * arrayref)
{
  int32_t length = arrayref[0];
  char * buf = (char *)&arrayref[1];
  print_string(buf, length);
}

void native_java_io_printstream_write_1(uint32_t * args)
{
  uint32_t * arrayref = (uint32_t *)args[0];
  native_java_io_printstream_write(arrayref);
}

void native_java_io_printstream_write_2(uint32_t * args)
{
  //uint32_t this = args[0];
  uint32_t * arrayref = (uint32_t *)args[1];
  native_java_io_printstream_write(arrayref);
}

void native_java_misc_memory_putU4_2(uint32_t * args)
{
  uint32_t * address = (uint32_t *)args[0];
  uint32_t value = args[1];
  *address = value;
}

void native_java_misc_memory_putU2_2(uint32_t * args)
{
  uint16_t * address = (uint16_t *)args[0];
  uint16_t value = args[1];
  *address = value;
}

void native_java_misc_memory_putU1_2(uint32_t * args)
{
  uint8_t * address = (uint8_t *)args[0];
  uint8_t value = args[1];
  *address = value;
}

uint32_t native_java_misc_memory_getU4_1(uint32_t * args)
{
  uint32_t * address = (uint32_t *)args[0];
  uint32_t value = *address;
  return value;
}

uint32_t native_java_misc_memory_getU2_1(uint32_t * args)
{
  uint16_t * address = (uint16_t *)args[0];
  uint16_t value = *address;
  return value;
}

uint32_t native_java_misc_memory_getU1_1(uint32_t * args)
{
  uint8_t * address = (uint8_t *)args[0];
  uint8_t value = *address;
  return value;
}

extern uint32_t store_queue[0x4000000] __asm("store_queue");

void native_java_misc_memory_putSQ1_2(uint32_t * args)
{
  #if defined(__dreamcast__)
  uint32_t * objectref = (uint32_t *)args[0];
  uint32_t address = (uint32_t)args[1];
  store_queue[0] = objectref[1];
  store_queue[1] = objectref[2];
  store_queue[2] = objectref[3];
  store_queue[3] = objectref[4];
  store_queue[4] = objectref[5];
  store_queue[5] = objectref[6];
  store_queue[6] = objectref[7];
  store_queue[7] = objectref[8];

  *((uint32_t*)0xff000038) = ((address >> 26) & 0b111) << 2;

  __asm__ volatile ("pref @%0"
                    :                       // output
                    : "r" (&store_queue[0]) // input
                    : "memory");
  #endif
}

uint32_t __attribute__ ((noinline)) __attribute__ ((optimize(0)))
native_java_lang_math_sin_1(uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = __builtin_sinf(arg);
  return *((uint32_t *)&value);
}

uint32_t __attribute__ ((noinline)) __attribute__ ((optimize(0)))
native_java_lang_math_cos_1(uint32_t * args)
{
  float arg = ((float *)args)[0];
  float value = __builtin_cosf(arg);
  return *((uint32_t *)&value);
}

#if defined(__dreamcast__)
#include "resources.inc.c"
#endif

uint32_t java_misc_resource_getresource_1(uint32_t * args)
{
  uint32_t * objectref = (uint32_t *)args[0];
  int32_t * arrayref = (int32_t *)objectref[1];
  int32_t name_length = (int32_t)arrayref[0];
  uint8_t * name = (uint8_t *)&arrayref[1];
  #if defined(__dreamcast__)
  uint32_t resource = find_resource(name, name_length);
  return resource;
  #else
  (void)name;
  (void)name_length;
  return 0;
  #endif
}
