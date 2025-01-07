#include "assert.h"
#include "parse_type.h"
#include "printf.h"

struct parse_type_ret parse_type(uint8_t * bytes, uint32_t length)
{
  if (bytes[length - 1] != ';') {
    assert(bytes[0] != '[');
    return (struct parse_type_ret){ bytes, length };
  }

  int ix = 0;
  while (bytes[ix] == '[') {
    ix += 1;
  }
  assert(bytes[ix] == 'L');
  ix += 1;

  return (struct parse_type_ret){ &bytes[ix], length - ix - 1 };
}

int parse_type_array_depth(uint8_t * bytes, uint32_t length)
{
  if (bytes[length - 1] != ';') {
    assert(bytes[0] != '[');
    return 0;
  }

  int ix = 0;
  while (bytes[ix] == '[') {
    ix += 1;
  }
  assert(bytes[ix] == 'L');
  return ix;
}
