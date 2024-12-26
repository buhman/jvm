#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void scif_init_wait();
void scif_init(int bit_rate);
void scif_character(const char c);

#ifdef __cplusplus
}
#endif
