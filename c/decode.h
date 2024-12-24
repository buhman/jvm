#pragma once

#include "frame.h"

uint32_t decode_print_instruction(const uint8_t * code, uint32_t pc);
void decode_execute_instruction(struct vm * vm, const uint8_t * code, uint32_t pc);
