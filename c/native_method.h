#pragma once

#include "vm.h"

struct hash_table_entry * native_init_hash_table(int * hash_table_length);

native_func_t * native_method_lookup(int native_hash_table_length,
                                     struct hash_table_entry * native_hash_table,
                                     struct constant * class_name_constant,
                                     struct constant * method_name_constant,
                                     struct constant * method_descriptor_constant);
