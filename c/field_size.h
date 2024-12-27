#pragma once

static inline int field_size(uint8_t c)
{
  switch (c) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    return 1;
  case 'D': [[fallthrough]];
  case 'J':
    return 2;
  default:
    assert(false);
  }
}

static inline int field_size_array(uint8_t c)
{
  switch (c) {
  case 'Z': [[fallthrough]]; // boolean
  case 'B': // byte
    return 1;
  case 'C': [[fallthrough]]; // char
  case 'S': // short
    return 2;
  case 'F': [[fallthrough]]; // float
  case 'I': [[fallthrough]]; // int
  case 'L': [[fallthrough]]; // classref
  case '[': // arrayref
    return 4;
  case 'D': [[fallthrough]];
  case 'J':
    return 8;
  default:
    assert(false);
  }
}
