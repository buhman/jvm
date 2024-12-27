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
      debugf("  %d: %d\n", i, aligned_s4(&table[i - lowbyte])); \
    } \
    debugf("default: %d\n", defaultbyte); \
  } while (0);

#define TABLESWITCH_NEXT_PC \
  (args + (3 * 4) + ((highbyte - lowbyte + 1) * 4))

#define LOOKUPSWITCH_ARGS                            \
  uint32_t args = ((pc + 1) + 3) & (~3);             \
  int32_t defaultbyte = aligned_s4(&code[args + 0]); \
  int32_t npairs = aligned_s4(&code[args + 4]);      \
  const int32_t * table = (const int32_t *)&code[args + 8];

#define LOOKUPSWITCH_PRINT_ARGS()                                       \
  do {                                                                  \
    for (int i = 0; i < npairs; i++) {                                  \
      debugf("  %d: %d\n", aligned_s4(&table[i * 2]), aligned_s4(&table[i * 2 + 1])); \
    }                                                                   \
    debugf("default: %d\n", defaultbyte);                               \
  } while (0);

#define LOOKUPSWITCH_NEXT_PC \
  (args + (2 * 4) + (npairs * 2 * 4))

#define WIDE_ARGS                               \
  uint32_t opcode = code[pc + 1];               \
  uint32_t index = _u2(&code[pc + 2]);          \
  uint32_t wide_next_pc = pc + 4;               \
  int32_t _const;

#define WIDE_IMPL()                             \
  switch (opcode) {                             \
  case 21: /* iload */                          \
    op_iload(vm, index);                        \
    break;                                      \
  case 22: /* lload */                          \
    op_lload(vm, index);                        \
    break;                                      \
  case 23: /* fload */                          \
    op_fload(vm, index);                        \
    break;                                      \
  case 24: /* dload */                          \
    op_dload(vm, index);                        \
    break;                                      \
  case 25: /* aload */                          \
    op_aload(vm, index);                        \
    break;                                      \
  case 54: /* istore */                         \
    op_istore(vm, index);                       \
    break;                                      \
  case 56: /* fstore */                         \
    op_fstore(vm, index);                       \
    break;                                      \
  case 58: /* astore */                         \
    op_astore(vm, index);                       \
    break;                                      \
  case 55: /* lstore */                         \
    op_lstore(vm, index);                       \
    break;                                      \
  case 57: /* dstore */                         \
    op_dstore(vm, index);                       \
    break;                                      \
  case 169: /* ret */                           \
    op_ret(vm, index);                          \
    break;                                      \
  case 132: /* iinc */                          \
    {                                           \
      _const = _s2(&code[pc + 4]);              \
      op_iinc(vm, index, _const);               \
      wide_next_pc = pc + 6;                    \
    }                                           \
    break;                                      \
  }                                             \
  vm->current_frame->next_pc = wide_next_pc;

#define WIDE_PRINT_ARGS()                       \
  switch (opcode) {                             \
  case 21: /* iload */                          \
    debugf(" iload   %5d ", index);             \
    break;                                      \
  case 22: /* lload */                          \
    debugf(" lload   %5d ", index);             \
    break;                                      \
  case 23: /* fload */                          \
    debugf(" fload   %5d ", index);             \
    break;                                      \
  case 24: /* dload */                          \
    debugf(" dload   %5d ", index);             \
    break;                                      \
  case 25: /* aload */                          \
    debugf(" aload   %5d ", index);             \
    break;                                      \
  case 54: /* istore */                         \
    debugf(" istore  %5d ", index);             \
    break;                                      \
  case 56: /* fstore */                         \
    debugf(" fstore  %5d ", index);             \
    break;                                      \
  case 58: /* astore */                         \
    debugf(" astore  %5d ", index);             \
    break;                                      \
  case 55: /* lstore */                         \
    debugf(" lstore  %5d ", index);             \
    break;                                      \
  case 57: /* dstore */                         \
    debugf(" dstore  %5d ", index);             \
    break;                                      \
  case 169: /* ret */                           \
    debugf(" ret     %5d ", index);             \
    break;                                      \
  case 132: /* iinc */                          \
    _const = _s2(&code[pc + 4]);                \
    debugf(" iinc    %5d %5d ", index, _const); \
    wide_next_pc = pc + 6;                      \
    break;                                      \
  }

#define WIDE_NEXT_PC wide_next_pc

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#include "decode.inc.c"
#pragma GCC diagnostic pop
