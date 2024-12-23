#include <stdio.h>
#include <assert.h>

#include "debug_class_file.h"
#include "file.h"

int main(int argc, char * argv[])
{
  assert(argc >= 2);
  uint8_t * buf = file_read(argv[1]);

  struct class_file * class_file = class_file_parse(buf);
  print_class_file(class_file);

  return 0;
}
