#pragma once

#include "native_types.h"
#include "vm.h"
#include "compat.h"

struct backtrace_entry {
  struct class_file * class_file;
  struct method_info * method_info;
  int pc;
};

struct objectref * backtrace_allocate(struct vm * vm);

void backtrace_print(struct objectref * objectref);
