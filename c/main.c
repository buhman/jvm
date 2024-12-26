#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "frame.h"
#include "class_resolver.h"
#include "string.h"
#include "file.h"

static struct hash_table_entry * load_from_filenames(const char * filenames[], int length, int * hash_table_length)
{
  const uint8_t ** class_names = (const uint8_t **)filenames;
  int class_names_length[length];
  uint8_t * buffers[length];
  size_t file_size[length];

  for (int i = 0; i < length; i++) {
    uint32_t filename_length = string_length(filenames[i]);
    const char * suffix = ".class";
    uint32_t suffix_length = string_length(suffix);
    const char * filename_suffix = &filenames[i][filename_length - suffix_length];
    if (filename_length <= suffix_length || !string_equal(suffix, filename_suffix)) {
      printf("invalid class filename: %s\n", filenames[i]);
      continue;
    }
    class_names_length[i] = filename_length - suffix_length;
    printf("load class: %s\n", filenames[i]);

    buffers[i] = file_read(filenames[i], &file_size[i]);
  }

  struct hash_table_entry * class_hash_table = class_resolver_load_from_buffers(class_names,
                                                                                class_names_length,
                                                                                buffers,
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

  const char * main_class = argv[1];

  const char ** class_filenames = &argv[2];
  int num_class_filenames = argc - 2;

  int class_hash_table_length;
  struct hash_table_entry * class_hash_table = load_from_filenames(class_filenames, num_class_filenames, &class_hash_table_length);

  struct class_entry * class_entry = class_resolver_lookup_class(class_hash_table_length,
                                                                 class_hash_table,
                                                                 (const uint8_t *)main_class,
                                                                 string_length(main_class));
  assert(class_entry != nullptr);

  const char * method_name = "main";
  int method_name_length = string_length(method_name);
  const char * method_descriptor = "()V";
  int method_descriptor_length = string_length(method_descriptor);

  int methods_hash_table_length = class_entry->methods.length;
  struct hash_table_entry * methods_hash_table = class_entry->methods.entry;

  struct method_info * method_info = class_resolver_lookup_method(methods_hash_table_length,
                                                                  methods_hash_table,
                                                                  (const uint8_t *)method_name,
                                                                  method_name_length,
                                                                  (const uint8_t *)method_descriptor,
                                                                  method_descriptor_length);
  assert(method_info != nullptr);

  struct vm vm;
  vm.class_hash_table.entry = class_hash_table;
  vm.class_hash_table.length = class_hash_table_length;

  vm.frame_stack.ix = 0;
  vm.frame_stack.capacity = 1024;
  struct frame frames[vm.frame_stack.capacity];
  vm.frame_stack.frame = frames;

  vm.data_stack.ix = 0;
  vm.data_stack.capacity = 0x100000;
  uint32_t data[vm.data_stack.capacity];
  vm.data_stack.data = data;

  struct frame * entry_frame = stack_push_frame(&vm.frame_stack, 1);
  struct Code_attribute code;
  code.max_locals = 0;
  code.max_stack = 0;
  entry_frame->code = &code;
  entry_frame->local_variable = 0;
  entry_frame->operand_stack = 0;
  entry_frame->operand_stack_ix = 0;

  vm_static_method_call(&vm, class_entry, method_info);
  vm_execute(&vm);
}
