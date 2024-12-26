#pragma once

#if defined(__linux__)
#include "printf_hosted.h"
#elif defined(_WIN32)
#include "printf_hosted.h"
#elif defined(__APPLE__)
#include "printf_hosted.h"
#else
#include "printf_dreamcast.h"
#endif
