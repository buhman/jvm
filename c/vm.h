#pragma once

#include "frame_stack.h"
#include "class_file.h"

bool vm_initialize_class(struct vm * vm, struct class_entry * class_entry);
void vm_special_method_call(struct vm * vm, struct class_entry * class_entry, struct method_entry * method_entry);
void vm_static_method_call(struct vm * vm, struct class_entry * class_entry, struct method_entry * method_entry);
void vm_method_return(struct vm * vm);
void vm_execute(struct vm * vm);
struct vm * vm_start(int class_hash_table_length,
                     struct hash_table_entry * class_hash_table,
                     int native_hash_table_length,
                     struct hash_table_entry * native_hash_table,
                     const uint8_t * main_class_name,
                     int main_class_name_length);
int descriptor_nargs(struct constant * descriptor_constant, uint8_t * return_type);
void vm_exception(struct vm * vm, struct objectref * objectref);
