#include <stdlib.h>

#include "assert.h"
#include "debug_class_file.h"
#include "file.h"
#include "printf.h"

int main(int argc, char * argv[])
{
  assert(argc >= 2);
  size_t file_size;
  uint8_t * buf = file_read(argv[1], &file_size);

  struct class_file * class_file = class_file_parse(buf);
  print_class_file(class_file);

  (void)file_size;
  free(buf);

  return 0;
}
