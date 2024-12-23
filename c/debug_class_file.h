#pragma once

#include "class_file.h"

void print_constant(struct constant * constant);
void print_attribute(const char * indent, struct attribute_info * attribute, struct constant * constant_pool);
void print_class_file(struct class_file * class_file);
