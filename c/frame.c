#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include "class_file.h"
#include "file.h"
#include "memory.h"
#include "debug_class_file.h"
#include "bytes.h"
#include "decode.h"
#include "frame.h"

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

void vm_execute(struct vm * vm)
{
  printf("execute:\n");
  struct constant * class = &vm->current_thread.current_class->constant_pool[vm->current_thread.current_class->this_class - 1];
  print_constant(class);
  print_constant(&vm->current_thread.current_class->constant_pool[class->class.name_index - 1]);
  print_constant(&vm->current_thread.current_class->constant_pool[vm->current_thread.current_method->name_index - 1]);

  int code_name_index = find_code_name_index(vm->current_thread.current_class);
  assert(code_name_index > 0);
  printf("code_name_index %d\n", code_name_index);

  struct Code_attribute * code = get_code_attribute(code_name_index,
                                                    vm->current_thread.current_method->attributes_count,
                                                    vm->current_thread.current_method->attributes);
  assert(code != nullptr);

  vm->current_frame = stack_push_frame(&vm->frame_stack, 1);
  vm->current_frame->local_variable = stack_push_data(&vm->data_stack, code->max_locals);
  vm->current_frame->operand_stack = stack_push_data(&vm->data_stack, code->max_stack);
  vm->current_frame->operand_stack_ix = 0;

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
    decode_print_instruction(code->code, vm->current_thread.pc);
    uint32_t old_pc = vm->current_thread.pc;
    uint32_t next_pc = decode_execute_instruction(vm, code->code, vm->current_thread.pc);
    if (vm->current_thread.pc == old_pc) {
      // if the instruction did not branch, increment pc
      vm->current_thread.pc = next_pc;
    }

    if (vm->current_thread.pc >= code->code_length) {
      printf("terminate\n");
      break;
    }
  }
}

int main(int argc, char * argv[])
{
  assert(argc >= 2);
  uint8_t * buf = file_read(argv[1]);
  struct class_file * class_file = class_file_parse(buf);

  assert(class_file->magic == 0xcafebabe);
  assert(class_file->methods_count >= 1);

  struct vm vm;
  vm.current_thread.pc = 0;
  vm.current_thread.current_class = class_file;
  vm.current_thread.current_method = &class_file->methods[1];

  vm.frame_stack.ix = 0;
  vm.frame_stack.capacity = 1024;
  struct frame frames[vm.frame_stack.capacity];
  vm.frame_stack.frame = frames;

  vm.data_stack.ix = 0;
  vm.data_stack.capacity = 0x100000;
  uint32_t data[vm.data_stack.capacity];
  vm.data_stack.data = data;

  vm_execute(&vm);
}
