#include "native_types.h"
#include "printstream.h"
#include "printf.h"

void native_java_io_printstream_write_ba_1(struct vm * vm, uint32_t * args)
{
  struct arrayref * arrayref = (struct arrayref *)args[0];
  assert(arrayref != nullptr);
  print_bytes(arrayref->u8, arrayref->length);
}

void native_java_io_printstream_write_ca_1(struct vm * vm, uint32_t * args)
{
  struct arrayref * arrayref = (struct arrayref *)args[0];
  assert(arrayref != nullptr);
  print_chars(arrayref->u16, arrayref->length);
}

void native_java_io_printstream_write_s_1(struct vm * vm, uint32_t * args)
{
  struct objectref * objectref = (struct objectref *)args[0];
  assert(objectref != nullptr);
  struct arrayref * arrayref = objectref->aref[0];
  assert(arrayref != nullptr);
  print_chars(arrayref->u16, arrayref->length);
}
