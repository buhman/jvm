#include <stdio.h>

#include "libcinputstream.h"
#include "assert.h"
#include "native_types.h"

void native_jvm_internal_libcinputstream_open_1(struct vm * vm, uint32_t * args)
{
  struct arrayref * arrayref = (struct arrayref *)args[0];
  assert(arrayref != nullptr);
  assert(arrayref->length > 0);
  assert(arrayref->u8[arrayref->length - 1] == 0);
  FILE * file = fopen((const char *)arrayref->u8, "rb");
  assert(file != nullptr);

  operand_stack_push_u32(vm->current_frame, (uint32_t)file);
}

void native_jvm_internal_libcinputstream_available_1(struct vm * vm, uint32_t * args)
{
  FILE * file = (FILE *)args[0];
  assert(file != nullptr);

  int current = fseek(file, 0L, SEEK_CUR);
  int ret_end = fseek(file, 0L, SEEK_END);
  assert(ret_end != -1);
  int ftell_end = ftell(file);
  assert(ftell_end != -1);
  int ret_set = fseek(file, current, SEEK_SET);
  assert(ret_set != -1);

  assert(ftell_end >= current);
  int available = ftell_end - current;

  operand_stack_push_u32(vm->current_frame, available);
}

void native_jvm_internal_libcinputstream_close_1(struct vm * vm, uint32_t * args)
{
  FILE * file = (FILE *)args[0];
  assert(file != nullptr);
  int ret = fclose(file);
  assert(ret == 0);
}

void native_jvm_internal_libcinputstream_read_1(struct vm * vm, uint32_t * args)
{
  FILE * file = (FILE *)args[0];
  assert(file != nullptr);

  uint8_t buf[1];
  int32_t size = fread(buf, 1, 1, file);
  if (size == 0)
    operand_stack_push_u32(vm->current_frame, (uint32_t)-1);
  else
    operand_stack_push_u32(vm->current_frame, (uint32_t)buf[0]);
}
