#include <stdint.h>

#include "assert.h"
#include "decode.h"
#include "execute.h"
#include "bswap.h"
#include "printf.h"

static inline uint32_t _u4(const uint8_t * buf)
{
  uint32_t n =
      buf[0] << 24
    | buf[1] << 16
    | buf[2] << 8
    | buf[3] << 0
    ;
  return n;
}

static inline uint32_t _u2(const uint8_t * buf)
{
  uint32_t n =
      buf[0] << 8
    | buf[1] << 0
    ;
  return n;
}

static inline uint32_t _u1(const uint8_t * buf)
{
  uint32_t n = buf[0];
  return n;
}

static inline int32_t _s4(const uint8_t * buf)
{
  int32_t n =
      buf[0] << 24
    | buf[1] << 16
    | buf[2] << 8
    | buf[3] << 0
    ;
  return n;
}

static inline int32_t _s2(const uint8_t * buf)
{
  int16_t n =
      buf[0] << 8
    | buf[1] << 0
    ;
  return n;
}

static inline int32_t _s1(const uint8_t * buf)
{
  int8_t n = buf[0];
  return n;
}

static inline int32_t aligned_s4(const void * buf)
{
  uint32_t n = *((uint32_t *)buf);
  return BE_BSWAP32(n);
}

#define TABLESWITCH_ARGS                             \
  uint32_t args = ((pc + 1) + 3) & (~3);             \
  int32_t defaultbyte = aligned_s4(&code[args + 0]); \
  int32_t lowbyte = aligned_s4(&code[args + 4]);     \
  int32_t highbyte = aligned_s4(&code[args + 8]);    \
  const int32_t * table = (const int32_t *)&code[args + 12];

#define TABLESWITCH_PRINT_ARGS() \
  do { \
    for (int i = lowbyte; i <= highbyte; i++) { \
      printf("  %d: %d\n", i, aligned_s4(&table[i - lowbyte])); \
    } \
    printf("default: %d\n", defaultbyte); \
  } while (0);

#define TABLESWITCH_NEXT_PC \
  (args + (3 * 4) + ((highbyte - lowbyte + 1) * 4))

#define LOOKUPSWITCH_ARGS assert(false);

#define LOOKUPSWITCH_PRINT_ARGS()

#define LOOKUPSWITCH_NEXT_PC 0

#define WIDE_ARGS assert(false);

#define WIDE_PRINT_ARGS()

#define WIDE_NEXT_PC 0

#include "decode.inc.c"
