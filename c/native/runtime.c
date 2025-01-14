#include "runtime.h"
#include "memory_allocator.h"
#include "gc.h"

void native_java_lang_runtime_freememory_0(struct vm * vm, uint32_t * args)
{
  int32_t count = memory_count_free_memory();
  operand_stack_push_u32(vm->current_frame, count);
}

void native_java_lang_runtime_gc_0(struct vm * vm, uint32_t * args)
{
  gc_run(vm);
}

void native_java_lang_runtime_totalmemory_0(struct vm * vm, uint32_t * args)
{
  int32_t count = memory_count_total_memory();
  operand_stack_push_u32(vm->current_frame, count);
}
