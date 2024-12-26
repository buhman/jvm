#pragma once

static inline int string_length(const char * s)
{
  const char * si = s;
  while (*si != 0) {
    si++;
  }
  return si - s;
}

static inline void string_copy(char * dst, const char * src)
{
  while (*src != 0) {
    *dst++ = *src++;
  }
  *dst = 0;
}

static inline bool string_equal(const char * a, const char * b)
{
  int i = 0;
  while (a[i] != 0) {
    if (a[i] != b[i])
      return false;
    i += 1;
  }
  return b[i] == 0;
}
