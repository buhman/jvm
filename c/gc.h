#pragma once

#include "frame.h"

void gc_mark(struct vm * vm);
void gc_sweep();
