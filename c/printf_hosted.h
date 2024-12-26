#pragma once

#include <stdio.h>

#define debugf(fmt, ...) printf((fmt), __VA_ARGS__);
#define debugc(c) putc(stdout, c);
