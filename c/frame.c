#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include "class_file.h"
#include "memory.h"
#include "debug_class_file.h"
#include "bytes.h"
#include "decode.h"
#include "frame.h"
#include "class_resolver.h"
#include "string.h"

struct frame * stack_push_frame(struct stack * stack, int num_frames)
{
  struct frame * frame = &stack->frame[stack->ix];
  stack->ix += num_frames;
  assert(stack->ix <= stack->capacity);
  return frame;
}

struct frame * stack_pop_frame(struct stack * stack, int num_frames)
{
  stack->ix -= num_frames;
  assert(stack->ix >= 0);
  struct frame * frame = &stack->frame[stack->ix];
  return frame;
}

uint32_t * stack_push_data(struct stack * stack, int num_data)
{
  uint32_t * data = &stack->data[stack->ix];
  stack->ix += num_data;
  assert(stack->ix <= stack->capacity);
  return data;
}

uint32_t * stack_pop_data(struct stack * stack, int num_data)
{
  stack->ix -= num_data;
  assert(stack->ix >= 0);
  uint32_t * data = &stack->data[stack->ix];
  return data;
}

struct Code_attribute * get_code_attribute(int code_name_index,
                                           int attributes_count,
                                           struct attribute_info * attributes)
{
  for (int i = 0; i < attributes_count; i++) {
    if (attributes[i].attribute_name_index == code_name_index)
      return attributes[i].code;
  }
  return nullptr;
}

int find_code_name_index(struct class_file * class_file)
{
  for (int i = 0; i < class_file->constant_pool_count; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    if (constant->tag == CONSTANT_Utf8) {
      if (bytes_equal(constant->utf8.length, constant->utf8.bytes, "Code")) {
        return i + 1;
      }
    }
  }
  return 0;
}

static int descriptor_nargs(struct constant * descriptor_constant)
{
  assert(descriptor_constant->tag == CONSTANT_Utf8);
  assert(descriptor_constant->utf8.length >= 2);
  assert(descriptor_constant->utf8.bytes[0] == '(');

  int i = 1;
  int nargs = 0;
  while (i < descriptor_constant->utf8.length) {
    if (descriptor_constant->utf8.bytes[i] == ')')
      break;
    nargs += 1;
    i += 1;
  }
  assert(i + 2 == descriptor_constant->utf8.length);

  return nargs;
}

void vm_static_method_call(struct vm * vm, struct class_file * class_file, struct method_info * method_info)
{
  /* If the method is not native, the nargs argument values are popped from the
     operand stack. A new frame is created on the Java Virtual Machine stack for
     the method being invoked. The nargs argument values are consecutively made
     the values of local variables of the new frame, with arg1 in local variable
     0 (or, if arg1 is of type long or double, in local variables 0 and 1) and
     so on. The new frame is then made current, and the Java Virtual Machine pc
     is set to the opcode of the first instruction of the method to be
     invoked. Execution continues with the first instruction of the method.
  */

  int code_name_index = find_code_name_index(class_file);
  assert(code_name_index > 0);
  printf("code_name_index %d\n", code_name_index);

  struct Code_attribute * code = get_code_attribute(code_name_index,
                                                    method_info->attributes_count,
                                                    method_info->attributes);
  assert(code != nullptr);

  struct frame * old_frame = vm->current_frame;

  vm->current_frame = stack_push_frame(&vm->frame_stack, 1);
  vm->current_frame->code = code;
  vm->current_frame->local_variable = stack_push_data(&vm->data_stack, code->max_locals);
  vm->current_frame->operand_stack = stack_push_data(&vm->data_stack, code->max_stack);
  vm->current_frame->operand_stack_ix = 0;

  struct constant * descriptor_constant = &class_file->constant_pool[method_info->descriptor_index - 1];
  int nargs = descriptor_nargs(descriptor_constant);
  printf("nargs %d\n", nargs);
  for (int i = 0; i < nargs; i++) {
    uint32_t value = operand_stack_pop_u32(old_frame);
    vm->current_frame->local_variable[nargs - i - 1] = value;
  }
  vm->current_thread.pc = 0;
  vm->current_thread.current_class = class_file;
  vm->current_thread.current_method = method_info;
}

void vm_execute(struct vm * vm)
{
  printf("execute:\n");

  while (true) {
    printf("[  ");
    for (int i = 5; i > 0; i--) {
      if (i > vm->current_frame->operand_stack_ix) {
        printf("            ");
        continue;
      }
      int32_t value = vm->current_frame->operand_stack[vm->current_frame->operand_stack_ix - i];
      if (value > 65536)
        printf("0x%08x  ", value);
      else
        printf("%10d  ", value);
    }
    printf("]\n");
    decode_print_instruction(vm->current_frame->code->code, vm->current_thread.pc);
    uint32_t old_pc = vm->current_thread.pc;
    uint32_t next_pc = decode_execute_instruction(vm, vm->current_frame->code->code, vm->current_thread.pc);
    if (vm->current_thread.pc == old_pc) {
      // if the instruction did not branch, increment pc
      vm->current_thread.pc = next_pc;
    }

    if (vm->current_thread.pc >= vm->current_frame->code->code_length) {
      printf("terminate\n");
      break;
    }
  }
}

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

  const char * method_name = "test";
  int method_name_length = string_length(method_name);
  struct method_info * method_info = class_resolver_lookup_method(class_entry,
                                                                  (const uint8_t *)method_name,
                                                                  method_name_length);

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

  vm_static_method_call(&vm, class_entry->class_file, method_info);
  vm_execute(&vm);
}
