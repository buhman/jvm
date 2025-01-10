#pragma once

#include "frame.h"

void gc_mark(struct vm * vm);
void gc_sweep();
void gc_run(struct vm * vm);
