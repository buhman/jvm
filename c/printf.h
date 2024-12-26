#pragma once

#if defined(__dreamcast__)
#include "sh7091_scif.h"
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline void print_char(char c)
{
#if defined(__dreamcast__)
  scif_character(c);
#else
  fputc(c, stderr);
#endif
}

void print_string(const char * s, int length);
void print_cstring(const char * s);

void _printf(const char * format, ...);

#define printf(...) _printf(__VA_ARGS__)

#if defined(DEBUG_PRINT)
#define debugf(...) _printf(__VA_ARGS__)
#define debugc(c) print_char(c)
#define debugs(s) print_cstring(s)
#else
#define debugf(...)
#define debugc(c)
#define debugs(c)
#endif

#ifdef __cplusplus
}
#endif
