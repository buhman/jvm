#pragma once

static inline void print_char(char c)
{
  scif_character(c);
}

void print_string(const char * s, int length)
{
  for (int i = 0; i < length; i++) {
    print_char(s[i]);
  }
}

#define printf(...) _printf(__VA_ARGS__)
#define debugf(...) _printf(__VA_ARGS__)
#define debugc(c) print_char(c)
