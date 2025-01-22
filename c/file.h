#pragma once

#include <stdint.h>
#include <stddef.h>
#include "compat.h"

uint8_t * file_read(const char * path, size_t * file_size);
