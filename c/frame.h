#pragma once

#include <assert.h>

#include "class_file.h"

struct frame {
  struct Code_attribute * code;
  uint32_t * local_variable;
  uint32_t * operand_stack;
  uint16_t operand_stack_ix;
};

struct thread {
  uint32_t pc;
  struct class_file * current_class;
  struct method_info * current_method;
};

struct stack {
  union {
    struct frame * frame;
    uint32_t * data;
  };
  uint32_t ix;
  uint32_t capacity;
};

struct vm {
  struct stack frame_stack;
  struct stack data_stack;
  struct thread current_thread;
  struct frame * current_frame;
  struct {
    int length;
    struct hash_table_entry * entry;
  } class_hash_table;
};

static inline void operand_stack_push_u32(struct frame * frame, uint32_t value)
{
  frame->operand_stack[frame->operand_stack_ix] = value;
  frame->operand_stack_ix++;
}

static inline uint32_t operand_stack_pop_u32(struct frame * frame)
{
  frame->operand_stack_ix--;
  uint32_t value = frame->operand_stack[frame->operand_stack_ix];
  frame->operand_stack[frame->operand_stack_ix] = -1;
  return value;
}

static inline void operand_stack_dup_u32(struct frame * frame)
{
  uint32_t value = frame->operand_stack[frame->operand_stack_ix - 1];
  frame->operand_stack[frame->operand_stack_ix] = value;
  frame->operand_stack_ix++;
}

void vm_static_method_call(struct vm * vm, struct class_file * class_file, struct method_info * method_info);
