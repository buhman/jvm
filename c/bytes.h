#include <stdint.h>

#include "malloc.h"

static inline uint32_t parse_u4(const uint8_t ** buf)
{
  uint32_t n =
      (*buf)[0] << 24
    | (*buf)[1] << 16
    | (*buf)[2] << 8
    | (*buf)[3] << 0
    ;
  (*buf) += 4;
  return n;
}

static inline uint32_t parse_u2(const uint8_t ** buf)
{
  uint32_t n =
      (*buf)[0] << 8
    | (*buf)[1] << 0
    ;
  (*buf) += 2;
  return n;
}

static inline uint32_t parse_u1(const uint8_t ** buf)
{
  uint32_t n = (*buf)[0];
  (*buf) += 1;
  return n;
}

static inline int32_t parse_s4(const uint8_t ** buf)
{
  int32_t n =
      (*buf)[0] << 24
    | (*buf)[1] << 16
    | (*buf)[2] << 8
    | (*buf)[3] << 0
    ;
  (*buf) += 4;
  return n;
}

static inline int32_t parse_s2(const uint8_t ** buf)
{
  int16_t n =
      (*buf)[0] << 8
    | (*buf)[1] << 0
    ;
  (*buf) += 2;
  return n;
}

static inline int32_t parse_s1(const uint8_t ** buf)
{
  int8_t n = (*buf)[0];
  (*buf) += 1;
  return n;
}

static inline void * parse_bytes(const uint8_t ** buf, int length)
{
  uint8_t * dest = malloc_class_arena(length);
  for (int i = 0; i < length; i++)
    dest[i] = (*buf)[i];
  (*buf) += length;
  return dest;
}

static inline bool bytes_equal_string(int length, const uint8_t * a, const char * b)
{
  int i;
  for (i = 0; i < length; i++) {
    if (((char)a[i]) != ((char)b[i]))
      return false;
  }
  return b[i] == 0;
}

static inline bool bytes_equal_bytes(const uint8_t * a, int a_length, const uint8_t * b, int b_length)
{
  if (a_length != b_length)
    return false;

  for (int i = 0; i < a_length; i++) {
    if ((a[i]) != (b[i]))
      return false;
  }
  return true;
}

static inline bool constant_equal(struct constant * constant, const char * s)
{
  assert(constant->tag == CONSTANT_Utf8);
  return bytes_equal_string(constant->utf8.length, constant->utf8.bytes, s);
}
