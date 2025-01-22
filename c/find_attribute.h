#pragma once

#include "class_file.h"
#include "compat.h"

int find_code_name_index(struct class_file * class_file);
int find_constantvalue_name_index(struct class_file * class_file);
int find_linenumbertable_name_index(struct class_file * class_file);
struct attribute_info * find_attribute(int name_index,
                                       int attributes_count,
                                       struct attribute_info * attributes);
