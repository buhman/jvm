#pragma once

#include "assert.h"
#include "class_file.h"
#include "class_resolver.h"

struct frame {
  struct class_entry * class_entry;
  struct method_info * method;
  struct Code_attribute * code;
  uint32_t * local_variable;
  uint32_t * operand_stack;
  uint32_t pc;
  uint32_t next_pc;
  int32_t operand_stack_ix;
  uint8_t initialization_frame;
  uint8_t return_type;
};

struct stack {
  union {
    struct frame * frame;
    uint32_t * data;
  };
  int32_t ix;
  int32_t capacity;
};

struct vm {
  struct stack frame_stack;
  struct stack data_stack;
  struct frame * current_frame;
  struct {
    int length;
    struct hash_table_entry * entry;
  } class_hash_table;
};
static inline struct frame * stack_push_frame(struct stack * stack, int num_frames)
{
  struct frame * frame = &stack->frame[stack->ix];
  stack->ix += num_frames;
  assert(stack->ix <= stack->capacity);
  return frame;
}

static inline struct frame * stack_pop_frame(struct stack * stack, int num_frames)
{
  stack->ix -= num_frames;
  assert(stack->ix >= 0);
  struct frame * frame = &stack->frame[stack->ix - 1];
  return frame;
}

static inline uint32_t * stack_push_data(struct stack * stack, int num_data)
{
  uint32_t * data = &stack->data[stack->ix];
  stack->ix += num_data;
  assert(stack->ix <= stack->capacity);
  return data;
}

static inline uint32_t * stack_pop_data(struct stack * stack, int num_data)
{
  stack->ix -= num_data;
  assert(stack->ix >= 0);
  uint32_t * data = &stack->data[stack->ix];
  return data;
}

static inline void operand_stack_push_u32(struct frame * frame, uint32_t value)
{
  frame->operand_stack[frame->operand_stack_ix] = value;
  frame->operand_stack_ix++;
}

static inline uint32_t operand_stack_peek_u32(struct frame * frame, int index)
{
  assert((frame->operand_stack_ix - index) >= 0);
  uint32_t value = frame->operand_stack[frame->operand_stack_ix - index];
  return value;
}

static inline uint32_t operand_stack_pop_u32(struct frame * frame)
{
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
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

static inline void operand_stack_push_f32(struct frame * frame, float f)
{
  uint32_t value = *((uint32_t *)&f);
  frame->operand_stack[frame->operand_stack_ix] = value;
  frame->operand_stack_ix++;
}

static inline float operand_stack_pop_f32(struct frame * frame)
{
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
  uint32_t value = frame->operand_stack[frame->operand_stack_ix];
  frame->operand_stack[frame->operand_stack_ix] = -1;
  float f = *((float *)&value);
  return f;
}

static inline void operand_stack_push_u64(struct frame * frame, uint64_t value)
{
  frame->operand_stack[frame->operand_stack_ix] = (uint32_t)(value >> 0);
  frame->operand_stack_ix++;
  frame->operand_stack[frame->operand_stack_ix] = (uint32_t)(value >> 32);
  frame->operand_stack_ix++;
}

static inline uint64_t operand_stack_pop_u64(struct frame * frame)
{
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
  uint64_t high = frame->operand_stack[frame->operand_stack_ix];
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
  uint64_t low = frame->operand_stack[frame->operand_stack_ix];
  uint64_t value = (high << 32) | (low << 0);
  return value;
}

static inline void operand_stack_push_f64(struct frame * frame, double f)
{
  uint64_t value = *((uint64_t *)&f);
  frame->operand_stack[frame->operand_stack_ix] = (uint32_t)(value >> 0);
  frame->operand_stack_ix++;
  frame->operand_stack[frame->operand_stack_ix] = (uint32_t)(value >> 32);
  frame->operand_stack_ix++;
}

static inline double operand_stack_pop_f64(struct frame * frame)
{
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
  uint64_t high = frame->operand_stack[frame->operand_stack_ix];
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
  uint64_t low = frame->operand_stack[frame->operand_stack_ix];
  uint64_t value = (high << 32) | (low << 0);
  double f = *((double *)&value);
  return f;
}

bool vm_initialize_class(struct vm * vm, struct class_entry * class_entry);
void vm_special_method_call(struct vm * vm, struct class_entry * class_entry, struct method_info * method_info);
void vm_static_method_call(struct vm * vm, struct class_entry * class_entry, struct method_info * method_info);
void vm_method_return(struct vm * vm);
void vm_execute(struct vm * vm);
void vm_start(int class_hash_table_length,
              struct hash_table_entry * class_hash_table,
              const uint8_t * main_class,
              int main_class_length);
