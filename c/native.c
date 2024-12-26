#include "native.h"
#include "printf.h"

void native_java_io_printstream_write(uint32_t * arrayref)
{
  uint32_t length = arrayref[0];
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
