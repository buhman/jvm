#pragma once

#include "frame.h"

void native_method_call(struct vm * vm,
                        struct constant * class_name_constant,
                        struct constant * method_name_constant,
                        struct constant * method_descriptor_constant,
                        uint32_t * args);
struct hash_table_entry * native_init_hash_table(int * hash_table_length);
