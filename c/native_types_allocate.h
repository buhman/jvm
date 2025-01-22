#pragma once

#include "native_types.h"
#include "gc.h"
#include "vm.h"
#include "memory_allocator.h"
#include "compat.h"

static inline void * gc_memory_allocate(struct vm * vm, int size)
{
  void * mem = memory_allocate(size);
  if (mem == nullptr) {
    gc_run(vm);
    mem = memory_allocate(size);
  }
  return mem;
}

static inline struct arrayref * prim_array_allocate(struct vm * vm, int element_size, int count)
{
  int32_t size = count * element_size + (sizeof (struct arrayref));
  struct arrayref * arrayref = gc_memory_allocate(vm, size);
  if (arrayref != nullptr) {
    arrayref->tag.type = TAG_TYPE_PRIM_ARRAY;
    arrayref->tag.mark = 0;
    arrayref->length = count;
  }
  return arrayref;
}

static inline struct arrayref * ref_array_allocate(struct vm * vm, int count)
{
  int32_t size = count * (sizeof (void *)) + (sizeof (struct arrayref));
  struct arrayref * arrayref = gc_memory_allocate(vm, size);
  if (arrayref != nullptr) {
    arrayref->tag.type = TAG_TYPE_REF_ARRAY;
    arrayref->tag.mark = 0;
    arrayref->length = count;
  }
  return arrayref;
}

static inline struct objectref * obj_allocate(struct vm * vm, int num_fields)
{
  int32_t size = num_fields * (sizeof (void *)) + (sizeof (struct objectref));
  struct objectref * objectref = gc_memory_allocate(vm, size);
  if (objectref != nullptr) {
    objectref->tag.type = TAG_TYPE_OBJECT;
    objectref->tag.mark = 0;
  }
  return objectref;
}
