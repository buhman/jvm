#pragma once

#include <stdint.h>

#include "assert.h"
#include "memory_allocator.h"

enum tag_type {
  TAG_TYPE_OBJECT = -30741,
  TAG_TYPE_REF_ARRAY = 23240,
  TAG_TYPE_PRIM_ARRAY = -5251,
};

struct tag {
  int8_t mark;
  int8_t _res;
  int16_t type;
};

static_assert((sizeof (struct tag)) == 4);

struct objectref {
  struct tag tag;
  struct class_entry * class_entry;
  union {
    struct objectref * oref[0];
    struct arrayref * aref[0];
    uint32_t u32[0];
  };
};

static_assert((sizeof (struct objectref)) == 8);

struct arrayref {
  struct tag tag;
  struct class_entry * class_entry;
  int32_t length;
  union {
    // object array:
    struct objectref * oref[0];
    struct arrayref * aref[0];
    void * ref[0];
    // primitive array:
    uint8_t u8[0];
    uint16_t u16[0];
    uint32_t u32[0];
    uint64_t u64[0];
  };
};

static_assert((sizeof (struct arrayref)) == 12);

enum ARRAY_TYPE {
  T_BOOLEAN = 4, // 1 byte
  T_CHAR = 5,    // 2 bytes
  T_FLOAT = 6,   // 4 bytes
  T_DOUBLE = 7,  // 8 bytes
  T_BYTE = 8,    // 1 byte
  T_SHORT = 9,   // 2 bytes
  T_INT = 10,    // 4 bytes
  T_LONG = 11,   // 8 bytes
};

static inline int array_element_size(int atype)
{
  switch (atype) {
  case T_BOOLEAN: /* fall through */; // 1 byte
  case T_BYTE:                        // 1 byte
    return 1;
    break;
  case T_CHAR:    /* fall through */; // 2 bytes
  case T_SHORT:                       // 2 bytes
    return 2;
    break;
  case T_FLOAT:   /* fall through */; // 4 bytes
  case T_INT:                         // 4 bytes
    return 4;
    break;
  case T_DOUBLE:  /* fall through */; // 8 bytes
  case T_LONG:                        // 8 bytes
    return 8;
    break;
  default:
    assert(!"invalid atype");
    break;
  }
}
