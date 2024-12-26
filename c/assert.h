#pragma once

#if defined(__linux__)
#include "assert_hosted.h"
#elif defined(_WIN32)
#include "assert_hosted.h"
#elif defined(__APPLE__)
#include "assert_hosted.h"
#else
#include "assert_dreamcast.h"
#endif
