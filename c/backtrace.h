#pragma once

#include "frame.h"

struct backtrace_entry {
  struct class_file * class_file;
  struct method_info * method_info;
  int pc;
};

struct backtrace {
  int num_entries;
  struct backtrace_entry * entry;
};

struct backtrace * backtrace_allocate(struct vm * vm);

void backtrace_print(struct backtrace * backtrace);
