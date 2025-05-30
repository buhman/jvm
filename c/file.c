#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "file.h"
#include "assert.h"
#include "printf.h"

uint8_t * file_read(const char * path, size_t * file_size)
{
  int ret;
  //debugf("file_read: %s\n", path);
  FILE * f = fopen(path, "rb");
  if (f == nullptr)
    printf("file_read: %s\n", path);
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

  *file_size = size;

  return buf;
}
