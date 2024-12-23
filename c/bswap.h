#pragma once

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BE_BSWAP32(n) (n)
#else
#define BE_BSWAP32(n) (__builtin_bswap32(n))
#endif
