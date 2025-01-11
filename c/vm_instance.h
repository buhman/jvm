#pragma once

#include "frame.h"

struct objectref * vm_instance_create(struct vm * vm, const char * class_name);
struct objectref * vm_instance_string_from_constant(struct vm * vm, struct constant * constant);
