#pragma once

#include "class_file.h"
#include "class_resolver.h"

void debug_print__string(const uint8_t * bytes, int length);
void debug_print__constant__utf8_string(struct constant * constant);
void debug_print__class_entry__class_name(struct class_entry * class_entry);
void debug_print__constant__method_name(struct constant * name_constant, struct constant * descriptor_constant);
void debug_print__method_info__method_name(struct class_entry * class_entry, struct method_info * method_info);

void print__constant__utf8_string(struct constant * constant);
void print__class_entry__class_name(struct class_entry * class_entry);
void print__constant__method_name(struct constant * name_constant, struct constant * descriptor_constant);
void print__method_info__method_name(struct class_entry * class_entry, struct method_info * method_info);
