#pragma once

#include "vm.h"
#include "compat.h"

void gc_mark(struct vm * vm);
void gc_sweep();
void gc_run(struct vm * vm);
