#include "native_types.h"
#include "printstream.h"
#include "printf.h"

void native_java_io_printstream_write_1(struct vm * vm, uint32_t * args)
{
  struct arrayref * arrayref = (struct arrayref *)args[0];
  print_string((const char *)arrayref->u8, arrayref->length);
}
