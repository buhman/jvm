#pragma once

#include "printf.h"

#define assert(b)                                                       \
  do {                                                                  \
    if (!(b)) {                                                         \
      printf("%s:%d %s: assertion `%s` failed\n", __FILE__, __LINE__, __func__, #b); \
      while (1);                                                        \
    }                                                                   \
  } while (0);
