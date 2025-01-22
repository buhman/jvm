#pragma once

static inline int field_size(uint8_t c)
{
  switch (c) {
  case 'B': /* fall through */;
  case 'C': /* fall through */;
  case 'F': /* fall through */;
  case 'I': /* fall through */;
  case 'L': /* fall through */;
  case 'S': /* fall through */;
  case 'Z': /* fall through */;
  case '[':
    return 1;
  case 'D': /* fall through */;
  case 'J':
    return 2;
  default:
    assert(false);
  }
}

static inline int field_size_array(uint8_t c)
{
  switch (c) {
  case 'Z': /* fall through */; // boolean
  case 'B': // byte
    return 1;
  case 'C': /* fall through */; // char
  case 'S': // short
    return 2;
  case 'F': /* fall through */; // float
  case 'I': /* fall through */; // int
  case 'L': /* fall through */; // classref
  case '[': // arrayref
    return 4;
  case 'D': /* fall through */;
  case 'J':
    return 8;
  default:
    assert(false);
  }
}
