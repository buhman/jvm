#pragma once

#include <stdio.h>

#define debugf(...) printf(__VA_ARGS__)
#define debugc(c) putc(stdout, c)
