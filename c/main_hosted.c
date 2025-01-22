#include <stdlib.h>

#include "class_resolver.h"
#include "file.h"
#include "malloc.h"
#include "memory_allocator.h"
#include "native_method.h"
#include "printf.h"
#include "string.h"

void * memset(void * s, int c, size_t n);

static struct hash_table_entry * load_from_filenames(const char * filenames[], int length, int * hash_table_length)
{
  uint8_t * buffers[length];
  size_t file_size[length];

  for (int i = 0; i < length; i++) {
    debugf("load class: %s\n", filenames[i]);
    buffers[i] = file_read(filenames[i], &file_size[i]);
  }

  memory_reset_free_list();
  malloc_class_arena_reset();

  struct hash_table_entry * class_hash_table = class_resolver_load_from_buffers((const uint8_t **)buffers,
                                                                                length,
                                                                                hash_table_length);

  for (int i = 0; i < length; i++) {
    memset(buffers[i], 0, file_size[i]);
    free(buffers[i]);
  }

  return class_hash_table;
}

int main(int argc, const char * argv[])
{
  assert(argc >= 3);

  const uint8_t * main_class = (const uint8_t *)argv[1];
  int main_class_length = string_length((const char *)main_class);

  const char ** class_filenames = &argv[2];
  int num_class_filenames = argc - 2;

  int class_hash_table_length;
  struct hash_table_entry * class_hash_table = load_from_filenames(class_filenames, num_class_filenames, &class_hash_table_length);

  int native_hash_table_length;
  struct hash_table_entry * native_hash_table = native_init_hash_table(&native_hash_table_length);

  debugf("vm_start\n");

  struct vm * vm = vm_start(class_hash_table_length,
                            class_hash_table,
                            native_hash_table_length,
                            native_hash_table,
                            main_class,
                            main_class_length);

  vm_execute(vm);
}
