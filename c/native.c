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
