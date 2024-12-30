#include "printf.h"
#include "fatal.h"

void fatal_print__class_lookup_failed__from_string(const uint8_t * name, int length)
{
  printf("class lookup failed: ");
  for (int i = 0; i < length; i++) {
    printc(name[i]);
  }
  printc('\n');
}
