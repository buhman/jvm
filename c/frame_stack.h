#pragma once

#include <stdint.h>

#include "vm.h"
#include "assert.h"

enum initialization_state {
  CLASS_UNINITIALIZED,
  CLASS_INITIALIZING,
  CLASS_INITIALIZED,
};

struct method_entry {
  struct class_entry * class_entry;
  struct method_info * method_info;
  struct Code_attribute * code_attribute;
};

union attribute_entry {
  struct class_entry * class_entry;
  struct method_entry * method_entry;
  struct field_entry * field_entry;
  struct objectref * string_objectref;
};

struct field_entry {
  struct class_entry * class_entry;
  struct field_info * field_info;
  union {
    int32_t instance_index;
    int32_t static_index;
  };
};

struct class_entry {
  struct class_file * class_file;
  enum initialization_state initialization_state;
  union attribute_entry * attribute_entry;
  int32_t static_fields_count;
  int32_t * static_fields;
  int32_t instance_fields_count;

  struct {
    int length;
    struct hash_table_entry * entry;
  } fields;

  struct {
    int length;
    struct hash_table_entry * entry;
  } methods;
};

struct frame {
  struct class_entry * class_entry;
  struct method_info * method_info;
  struct Code_attribute * code_attribute;
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

static inline void operand_stack_push_ref(struct frame * frame, void * value)
{
  frame->operand_stack[frame->operand_stack_ix] = (uint32_t)value;
  frame->operand_stack_ix++;
}

static inline void * operand_stack_pop_ref(struct frame * frame)
{
  frame->operand_stack_ix--;
  assert(frame->operand_stack_ix >= 0);
  uint32_t value = frame->operand_stack[frame->operand_stack_ix];
  frame->operand_stack[frame->operand_stack_ix] = -1;
  return (void *)value;
}

static inline void * operand_stack_peek_ref(struct frame * frame, int index)
{
  assert((frame->operand_stack_ix - index) >= 0);
  uint32_t value = frame->operand_stack[frame->operand_stack_ix - index];
  return (void *)value;
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
