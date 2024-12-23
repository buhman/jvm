#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "file.h"

uint8_t * file_read(const char * path)
{
  int ret;
  FILE * f = fopen(path, "rb");
  assert(f != nullptr);
  ret = fseek(f, 0L, SEEK_END);
  assert(ret != -1);
  long size = ftell(f);
  assert(size != -1);
  ret = fseek(f, 0L, SEEK_SET);
  assert(ret != -1);

  uint8_t * buf = malloc(size);
  size_t read = fread(buf, 1, size, f);
  assert(read == size);

  return buf;
}
