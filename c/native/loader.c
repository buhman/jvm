#include "class_resolver.h"
#include "loader.h"
#include "malloc.h"
#include "native_method.h"
#include "native_types.h"
#include "printf.h"
#include "string.h"

static uint8_t loader_buffer[0x100000] __attribute__ ((aligned (32)));

void native_jvm_internal_loader_getbuffer_0(struct vm * vm, uint32_t * args)
{
  uint32_t value = (uint32_t)&loader_buffer[0];
  operand_stack_push_u32(vm->current_frame, value);
}

void native_jvm_internal_loader_load_2(struct vm * vm, uint32_t * args)
{
  struct arrayref * arrayref = (struct arrayref *)args[0];
  const uint8_t ** buffers = (const uint8_t **)&arrayref->u32[0];
  int32_t num_buffers = (int32_t)args[1];
  printf("native_jvm_internal_loader_load_2\n");
  debugf("num_buffers: %d\n", num_buffers);
  debugf("loader_buffer[0]: %p ; buffers[0]: %p\n", &loader_buffer[0], (uint32_t)buffers[0]);

  const uint8_t * main_class = (const uint8_t *)"Main";
  int main_class_length = string_length((const char *)main_class);

  memory_reset_free_list();
  malloc_class_arena_reset();

  int class_hash_table_length;
  struct hash_table_entry * class_hash_table = class_resolver_load_from_buffers(buffers,
                                                                                num_buffers,
                                                                                &class_hash_table_length);

  int native_hash_table_length;
  struct hash_table_entry * native_hash_table = native_init_hash_table(&native_hash_table_length);

  vm_start(class_hash_table_length,
           class_hash_table,
           native_hash_table_length,
           native_hash_table,
           main_class,
           main_class_length);
}
