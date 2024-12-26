#include "frame.h"
#include "class_resolver.h"
#include "string.h"

int main(int argc, const char * argv[])
{
  assert(argc >= 3);

  const char * main_class = argv[1];

  const char ** class_filenames = &argv[2];
  int num_class_filenames = argc - 2;

  int class_hash_table_length;
  struct hash_table_entry * class_hash_table = class_resolver_load_from_filenames(class_filenames, num_class_filenames, &class_hash_table_length);

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
