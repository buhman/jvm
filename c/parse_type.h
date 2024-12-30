#pragma once

#include <stdint.h>

struct parse_type_ret {
  uint8_t * bytes;
  uint32_t length;
};

struct parse_type_ret parse_type(uint8_t * bytes, uint32_t length);
int parse_type_array_depth(uint8_t * bytes, uint32_t length);
