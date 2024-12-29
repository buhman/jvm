#include "execute.h"
#include "memory_allocator.h"
#include "bswap.h"
#include "class_resolver.h"
#include "execute_helper.h"
#include "printf.h"
#include "field_size.h"

void op_aaload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  uint32_t * referencearray = (uint32_t *)&arrayref[1];
  uint32_t value = referencearray[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_aastore(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int32_t * referencearray = (int32_t *)&arrayref[1];
  referencearray[index] = value;
}

void op_aconst_null(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 0);
}

void op_aload(struct vm * vm, uint32_t index)
{
  uint32_t objectref = vm->current_frame->local_variable[index];
  operand_stack_push_u32(vm->current_frame, objectref);
}

void op_aload_0(struct vm * vm)
{
  uint32_t objectref = vm->current_frame->local_variable[0];
  operand_stack_push_u32(vm->current_frame, objectref);
}

void op_aload_1(struct vm * vm)
{
  uint32_t objectref = vm->current_frame->local_variable[1];
  operand_stack_push_u32(vm->current_frame, objectref);
}

void op_aload_2(struct vm * vm)
{
  uint32_t objectref = vm->current_frame->local_variable[2];
  operand_stack_push_u32(vm->current_frame, objectref);
}

void op_aload_3(struct vm * vm)
{
  uint32_t objectref = vm->current_frame->local_variable[3];
  operand_stack_push_u32(vm->current_frame, objectref);
}

void op_anewarray(struct vm * vm, uint32_t index)
{
  int32_t count = operand_stack_pop_u32(vm->current_frame);
  int32_t size = 4 * count + 4;
  int32_t * arrayref = memory_allocate(size);
  assert(arrayref != nullptr);
  arrayref[0] = count;

  /* All components of the new array are initialized to null, the default value
     for reference types */
  for (int i = 0; i < count; i++) {
    arrayref[i + 1] = 0;
  }

  operand_stack_push_u32(vm->current_frame, (uint32_t)arrayref);
}

void op_areturn(struct vm * vm)
{
  assert(vm->current_frame->return_type == 'L' || vm->current_frame->return_type == '[');
  vm_method_return(vm);
}

void op_arraylength(struct vm * vm)
{
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  int32_t length = arrayref[0];
  operand_stack_push_u32(vm->current_frame, length);
}

void op_astore(struct vm * vm, uint32_t index)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[index] = value;
}

void op_astore_0(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[0] = value;
}

void op_astore_1(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[1] = value;
}

void op_astore_2(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[2] = value;
}

void op_astore_3(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[3] = value;
}

void op_athrow(struct vm * vm)
{
  assert(!"op_athrow");
}

void op_baload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int8_t * bytearray = (int8_t *)&arrayref[1];
  int8_t value = bytearray[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_bastore(struct vm * vm)
{
  int8_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  debugf("%d %d\n", arrayref[0], index);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int8_t * bytearray = (int8_t *)&arrayref[1];
  bytearray[index] = value;
}

void op_bipush(struct vm * vm, int32_t byte)
{
  operand_stack_push_u32(vm->current_frame, byte);
}

void op_breakpoint(struct vm * vm)
{
  assert(!"op_breakpoint");
}

void op_caload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  uint16_t * chararray = (uint16_t *)&arrayref[1];
  uint16_t value = chararray[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_castore(struct vm * vm)
{
  uint16_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  uint16_t * chararray = (uint16_t *)&arrayref[1];
  chararray[index] = value;
}

void op_checkcast(struct vm * vm, uint32_t index)
{
  assert(!"op_checkcast");
}

void op_d2f(struct vm * vm)
{
  double value = operand_stack_pop_f64(vm->current_frame);
  float result = (float)value;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_d2i(struct vm * vm)
{
  double value = operand_stack_pop_f64(vm->current_frame);
  int32_t result = (int32_t)value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_d2l(struct vm * vm)
{
  double value = operand_stack_pop_f64(vm->current_frame);
  int64_t result = (int64_t)value;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_dadd(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  double result = value1 + value2;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_daload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int64_t * longarray = (int64_t *)&arrayref[1];
  int64_t value = longarray[index];
  operand_stack_push_u64(vm->current_frame, value);
}

void op_dastore(struct vm * vm)
{
  int64_t value = operand_stack_pop_u64(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int64_t * longarray = (int64_t *)&arrayref[1];
  longarray[index] = value;
}

void op_dcmpg(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  bool greater = value1 > value2;
  bool equal = value1 == value2;
  int32_t value;
  if (__builtin_isnan(value1) || __builtin_isnan(value2)) {
    value = 1;
  } else if (equal) {
    value = 0;
  } else if (greater) {
    value = 1;
  } else { // less than
    value = -1;
  }
  operand_stack_push_u32(vm->current_frame, value);
}

void op_dcmpl(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  bool greater = value1 > value2;
  bool equal = value1 == value2;
  int32_t value;
  if (__builtin_isnan(value1) || __builtin_isnan(value2)) {
    value = -1;
  } else if (equal) {
    value = 0;
  } else if (greater) {
    value = 1;
  } else { // less than
    value = -1;
  }
  operand_stack_push_u32(vm->current_frame, value);
}

void op_dconst_0(struct vm * vm)
{
  operand_stack_push_f64(vm->current_frame, 0.0f);
}

void op_dconst_1(struct vm * vm)
{
  operand_stack_push_f64(vm->current_frame, 1.0f);
}

void op_ddiv(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  double result = value1 / value2;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_dload(struct vm * vm, uint32_t index)
{
  uint32_t low = vm->current_frame->local_variable[index];
  uint32_t high = vm->current_frame->local_variable[index + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_dload_0(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[0];
  uint32_t high = vm->current_frame->local_variable[0 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_dload_1(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[1];
  uint32_t high = vm->current_frame->local_variable[1 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_dload_2(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[2];
  uint32_t high = vm->current_frame->local_variable[2 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_dload_3(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[3];
  uint32_t high = vm->current_frame->local_variable[3 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_dmul(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  double result = value1 * value2;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_dneg(struct vm * vm)
{
  double value = operand_stack_pop_f64(vm->current_frame);
  double result = -value;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_drem(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  double q = value1 / value2;
  double result = value1 - (value2 * (double)((int64_t)q));
  operand_stack_push_f64(vm->current_frame, result);
}

void op_dreturn(struct vm * vm)
{
  assert(vm->current_frame->return_type == 'D');
  vm_method_return(vm);
}

void op_dstore(struct vm * vm, uint32_t index)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[index + 1] = high;
  vm->current_frame->local_variable[index] = low;
}

void op_dstore_0(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[0 + 1] = high;
  vm->current_frame->local_variable[0] = low;
}

void op_dstore_1(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[1 + 1] = high;
  vm->current_frame->local_variable[1] = low;
}

void op_dstore_2(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[2 + 1] = high;
  vm->current_frame->local_variable[2] = low;
}

void op_dstore_3(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[3 + 1] = high;
  vm->current_frame->local_variable[3] = low;
}

void op_dsub(struct vm * vm)
{
  double value2 = operand_stack_pop_f64(vm->current_frame);
  double value1 = operand_stack_pop_f64(vm->current_frame);
  double result = value1 - value2;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_dup(struct vm * vm)
{
  operand_stack_dup_u32(vm->current_frame);
}

void op_dup2(struct vm * vm)
{
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
}

void op_dup2_x1(struct vm * vm)
{
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value3 = operand_stack_pop_u32(vm->current_frame);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
  operand_stack_push_u32(vm->current_frame, value3);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
}

void op_dup2_x2(struct vm * vm)
{
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value3 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value4 = operand_stack_pop_u32(vm->current_frame);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
  operand_stack_push_u32(vm->current_frame, value4);
  operand_stack_push_u32(vm->current_frame, value3);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
}

void op_dup_x1(struct vm * vm)
{
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  operand_stack_push_u32(vm->current_frame, value1);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
}

void op_dup_x2(struct vm * vm)
{
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value3 = operand_stack_pop_u32(vm->current_frame);
  operand_stack_push_u32(vm->current_frame, value1);
  operand_stack_push_u32(vm->current_frame, value3);
  operand_stack_push_u32(vm->current_frame, value2);
  operand_stack_push_u32(vm->current_frame, value1);
}

void op_f2d(struct vm * vm)
{
  float value = operand_stack_pop_f32(vm->current_frame);
  double result = (double)value;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_f2i(struct vm * vm)
{
  float value = operand_stack_pop_f32(vm->current_frame);
  int32_t result = (int32_t)value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_f2l(struct vm * vm)
{
  float value = operand_stack_pop_f32(vm->current_frame);
  int64_t result = (int64_t)value;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_fadd(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  float result = value1 + value2;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_faload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int32_t * intarray = (int32_t *)&arrayref[1];
  int32_t value = intarray[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fastore(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int32_t * intarray = (int32_t *)&arrayref[1];
  intarray[index] = value;
}

void op_fcmpg(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  bool greater = value1 > value2;
  bool equal = value1 == value2;
  int32_t value;
  if (__builtin_isnan(value1) || __builtin_isnan(value2)) {
    value = 1;
  } else if (equal) {
    value = 0;
  } else if (greater) {
    value = 1;
  } else { // less than
    value = -1;
  }
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fcmpl(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  bool greater = value1 > value2;
  bool equal = value1 == value2;
  int32_t value;
  if (__builtin_isnan(value1) || __builtin_isnan(value2)) {
    value = -1;
  } else if (equal) {
    value = 0;
  } else if (greater) {
    value = 1;
  } else { // less than
    value = -1;
  }
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fconst_0(struct vm * vm)
{
  operand_stack_push_f32(vm->current_frame, 0.0f);
}

void op_fconst_1(struct vm * vm)
{
  operand_stack_push_f32(vm->current_frame, 1.0f);
}

void op_fconst_2(struct vm * vm)
{
  operand_stack_push_f32(vm->current_frame, 2.0f);
}

void op_fdiv(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  float result = value1 / value2;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_fload(struct vm * vm, uint32_t index)
{
  uint32_t value = vm->current_frame->local_variable[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fload_0(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[0];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fload_1(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[1];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fload_2(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[2];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fload_3(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[3];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_fmul(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  float result = value1 * value2;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_fneg(struct vm * vm)
{
  float value = operand_stack_pop_f32(vm->current_frame);
  float result = -value;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_frem(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  float q = value1 / value2;
  float result = value1 - (value2 * (float)((int32_t)q));
  operand_stack_push_f32(vm->current_frame, result);
}

void op_freturn(struct vm * vm)
{
  assert(vm->current_frame->return_type == 'F');
  vm_method_return(vm);
}

void op_fstore(struct vm * vm, uint32_t index)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[index] = value;
}

void op_fstore_0(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[0] = value;
}

void op_fstore_1(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[1] = value;
}

void op_fstore_2(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[2] = value;
}

void op_fstore_3(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[3] = value;
}

void op_fsub(struct vm * vm)
{
  float value2 = operand_stack_pop_f32(vm->current_frame);
  float value1 = operand_stack_pop_f32(vm->current_frame);
  float result = value1 - value2;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_getfield(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct field_entry * field_entry;
  struct constant * field_descriptor_constant;
  class_entry_field_entry_from_constant_index(vm, index,
                                              &class_entry,
                                              &field_entry,
                                              &field_descriptor_constant);

  debugf("getfield instance_index %d\n", field_entry->instance_index);

  int32_t * objectref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(objectref != nullptr);
  int32_t * objectfields = &objectref[1];

  switch (field_descriptor_constant->utf8.bytes[0]) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    {
      uint32_t value = objectfields[field_entry->instance_index];
      operand_stack_push_u32(vm->current_frame, value);
    }
    break;
  case 'D': [[fallthrough]];
  case 'J':
    {
      uint32_t low = objectfields[field_entry->instance_index];
      uint32_t high = objectfields[field_entry->instance_index + 1];
      operand_stack_push_u32(vm->current_frame, low);
      operand_stack_push_u32(vm->current_frame, high);
    }
    break;
  default:
    assert(false);
  }
}

void op_getstatic(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct field_entry * field_entry;
  struct constant * field_descriptor_constant;
  class_entry_field_entry_from_constant_index(vm, index,
                                              &class_entry,
                                              &field_entry,
                                              &field_descriptor_constant);

  /*  On successful resolution of the field, the class or interface that
      declared the resolved field is initialized if that class or interface has
      not already been initialized (§5.5). */

  if (!vm_initialize_class(vm, class_entry))
    return;

  switch (field_descriptor_constant->utf8.bytes[0]) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    {
      uint32_t value = class_entry->static_fields[field_entry->static_index];
      operand_stack_push_u32(vm->current_frame, value);
    }
    break;
  case 'D': [[fallthrough]];
  case 'J':
    {
      uint32_t low = class_entry->static_fields[field_entry->static_index];
      uint32_t high = class_entry->static_fields[field_entry->static_index + 1];
      operand_stack_push_u32(vm->current_frame, low);
      operand_stack_push_u32(vm->current_frame, high);
    }
    break;
  default:
    assert(false);
  }
}

void op_goto(struct vm * vm, int32_t branch)
{
  vm->current_frame->next_pc = vm->current_frame->pc + branch;
}

void op_goto_w(struct vm * vm, int32_t branch)
{
  vm->current_frame->next_pc = vm->current_frame->pc + branch;
}

void op_i2b(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  int8_t result = value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_i2c(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  uint16_t result = value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_i2d(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  double result = (double)value;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_i2f(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  float result = (float)value;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_i2l(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  int64_t result = (int64_t)value;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_i2s(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  int16_t result = value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_iadd(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 + value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_iaload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int32_t * intarray = (int32_t *)&arrayref[1];
  int32_t value = intarray[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_iand(struct vm * vm)
{
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t result = value1 & value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_iastore(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int32_t * intarray = (int32_t *)&arrayref[1];
  intarray[index] = value;
}

void op_iconst_0(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 0);
}

void op_iconst_1(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 1);
}

void op_iconst_2(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 2);
}

void op_iconst_3(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 3);
}

void op_iconst_4(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 4);
}

void op_iconst_5(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, 5);
}

void op_iconst_m1(struct vm * vm)
{
  operand_stack_push_u32(vm->current_frame, -1);
}

void op_idiv(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 / value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_if_acmpeq(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 == value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_acmpne(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 != value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpeq(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 == value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpge(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 >= value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpgt(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 > value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmple(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 <= value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmplt(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 < value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpne(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 != value2) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifeq(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value == 0) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifge(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value >= 0) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifgt(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value > 0) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifle(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value <= 0) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_iflt(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value < 0) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifne(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value != 0) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifnonnull(struct vm * vm, int32_t branch)
{
  void * value = (void *)operand_stack_pop_u32(vm->current_frame);
  if (value != nullptr) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_ifnull(struct vm * vm, int32_t branch)
{
  void * value = (void *)operand_stack_pop_u32(vm->current_frame);
  if (value == nullptr) {
    vm->current_frame->next_pc = vm->current_frame->pc + branch;
  }
}

void op_iinc(struct vm * vm, uint32_t index, int32_t _const)
{
  int32_t value = vm->current_frame->local_variable[index];
  value += _const;
  vm->current_frame->local_variable[index] = value;
}

void op_iload(struct vm * vm, uint32_t index)
{
  uint32_t value = vm->current_frame->local_variable[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_iload_0(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[0];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_iload_1(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[1];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_iload_2(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[2];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_iload_3(struct vm * vm)
{
  uint32_t value = vm->current_frame->local_variable[3];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_impdep1(struct vm * vm)
{
  assert(!"op_impdep1");
}

void op_impdep2(struct vm * vm)
{
  assert(!"op_impdep2");
}

void op_imul(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 * value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_ineg(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t result = -value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_instanceof(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry =
    class_resolver_lookup_class_from_class_index(vm->class_hash_table.length,
                                                 vm->class_hash_table.entry,
                                                 vm->current_frame->class_entry,
                                                 index);
  assert(class_entry != nullptr);

  int32_t * objectref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  if (objectref == nullptr) {
    operand_stack_push_u32(vm->current_frame, 0);
  } else {
    int32_t value = objectref[0] == (int32_t)class_entry;
    operand_stack_push_u32(vm->current_frame, value);
  }
}

void op_invokedynamic(struct vm * vm, uint32_t index)
{
  assert(!"op_invokedynamic");
}

void op_invokeinterface(struct vm * vm, uint32_t index, uint32_t count)
{
  assert(!"op_invokeinterface");
}

void op_invokespecial(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct method_info * method_info;
  class_entry_method_info_from_constant_index(vm, index,
                                              &class_entry,
                                              &method_info);

  vm_special_method_call(vm, class_entry, method_info);
}

void op_invokestatic(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct method_info * method_info;
  class_entry_method_info_from_constant_index(vm, index,
                                              &class_entry,
                                              &method_info);

  /* On successful resolution of the method, the class or interface that
     declared the resolved method is initialized if that class or interface has
     not already been initialized (§5.5). */

  vm_static_method_call(vm, class_entry, method_info);
}

void op_invokevirtual(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct method_info * method_info;
  class_entry_method_info_from_constant_index(vm, index,
                                              &class_entry,
                                              &method_info);

  vm_special_method_call(vm, class_entry, method_info);
}

void op_ior(struct vm * vm)
{
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t result = value1 | value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_irem(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 % value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_ireturn(struct vm * vm)
{
  /*  Prior to pushing value onto the operand stack of the frame of the invoker,
      it may have to be converted. If the return type of the invoked method was
      byte, char, or short, then value is converted from int to the return type
      as if by execution of i2b, i2c, or i2s, respectively. If the return type
      of the invoked method was boolean, then value is narrowed from int to
      boolean by taking the bitwise AND of value and 1. */

  //  The current method must have return type boolean, byte, char, short, or int

  int32_t value = operand_stack_pop_u32(vm->current_frame);
  switch (vm->current_frame->return_type) {
  case 'Z': // boolean
    value = value & 1;
    break;
  case 'B': // byte
    value = (int8_t)value;
    break;
  case 'C': // char
    value = (uint16_t)value;
    break;
  case 'S': // short
    value = (int16_t)value;
    break;
  case 'I': // int
    value = (int32_t)value;
    break;
  default:
    debugf("invalid conversion: %c\n", vm->current_frame->return_type);
    assert(false);
  }
  operand_stack_push_u32(vm->current_frame, value);

  vm_method_return(vm);
}

void op_ishl(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int s = value2 & 0b11111;
  int32_t result = value1 << s;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_ishr(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int s = value2 & 0b11111;
  int32_t result = value1 >> s;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_istore(struct vm * vm, uint32_t index)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[index] = value;
}

void op_istore_0(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[0] = value;
}

void op_istore_1(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  debugf("istore_1: %d\n", value);
  if (value == 1) {
    debugf("istore1_1 == 1: %d\n", value);
    (void)(value);
  }
  vm->current_frame->local_variable[1] = value;
}

void op_istore_2(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[2] = value;
}

void op_istore_3(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[3] = value;
}

void op_isub(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 - value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_iushr(struct vm * vm)
{
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int s = value2 & 0b11111;
  uint32_t result = value1 >> s;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_ixor(struct vm * vm)
{
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t result = value1 ^ value2;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_jsr(struct vm * vm, int32_t branch)
{
  assert(!"op_jsr");
}

void op_jsr_w(struct vm * vm, int32_t branch)
{
  assert(!"op_jsr_w");
}

void op_l2d(struct vm * vm)
{
  int64_t value = operand_stack_pop_u64(vm->current_frame);
  double result = (double)value;
  operand_stack_push_f64(vm->current_frame, result);
}

void op_l2f(struct vm * vm)
{
  int64_t value = operand_stack_pop_u64(vm->current_frame);
  float result = (float)value;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_l2i(struct vm * vm)
{
  int64_t value = operand_stack_pop_u64(vm->current_frame);
  int32_t result = (int32_t)value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_ladd(struct vm * vm)
{
  int64_t value2 = operand_stack_pop_u64(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int64_t result = value1 + value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_laload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int64_t * longarray = (int64_t *)&arrayref[1];
  int64_t value = longarray[index];
  operand_stack_push_u64(vm->current_frame, value);
}

void op_land(struct vm * vm)
{
  uint64_t value2 = operand_stack_pop_u64(vm->current_frame);
  uint64_t value1 = operand_stack_pop_u64(vm->current_frame);
  uint64_t result = value1 & value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lastore(struct vm * vm)
{
  int64_t value = operand_stack_pop_u64(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int64_t * longarray = (int64_t *)&arrayref[1];
  longarray[index] = value;
}

void op_lcmp(struct vm * vm)
{
  int64_t value2 = operand_stack_pop_u64(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  bool greater = value1 > value2;
  bool equal = value1 == value2;
  int32_t value;
  if (equal) {
    value = 0;
  } else if (greater) {
    value = 1;
  } else { // less than
    value = -1;
  }
  operand_stack_push_u32(vm->current_frame, value);
}

void op_lconst_0(struct vm * vm)
{
  operand_stack_push_u64(vm->current_frame, 0);
}

void op_lconst_1(struct vm * vm)
{
  operand_stack_push_u64(vm->current_frame, 1);
}

void op_ldc(struct vm * vm, uint32_t index)
{
  struct constant * constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  if (constant->tag == CONSTANT_Integer || constant->tag == CONSTANT_Float) {
    int32_t value = constant->integer.bytes;
    operand_stack_push_u32(vm->current_frame, value);
  } else if (constant->tag == CONSTANT_String) {
    int32_t * objectref = class_resolver_lookup_string(vm->class_hash_table.length,
                                                       vm->class_hash_table.entry,
                                                       vm->current_frame->class_entry,
                                                       constant->string.string_index);
    operand_stack_push_u32(vm->current_frame, (uint32_t)objectref);
  } else {
    assert(false);
  }
}

void op_ldc2_w(struct vm * vm, uint32_t index)
{
  struct constant * constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  #ifdef DEBUG
  assert(constant->tag == CONSTANT_Long || constant->tag == CONSTANT_Double);
  #endif
  int64_t value = constant->_long.bytes;
  operand_stack_push_u64(vm->current_frame, value);
}

void op_ldc_w(struct vm * vm, uint32_t index)
{
  struct constant * constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  #ifdef DEBUG
  assert(constant->tag == CONSTANT_Integer || constant->tag == CONSTANT_Float);
  #endif
  int32_t value = constant->integer.bytes;
  operand_stack_push_u32(vm->current_frame, value);
}

void op_ldiv(struct vm * vm)
{
  int64_t value2 = operand_stack_pop_u64(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int64_t result = value1 / value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lload(struct vm * vm, uint32_t index)
{
  uint32_t low = vm->current_frame->local_variable[index];
  uint32_t high = vm->current_frame->local_variable[index + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_lload_0(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[0];
  uint32_t high = vm->current_frame->local_variable[0 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_lload_1(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[1];
  uint32_t high = vm->current_frame->local_variable[1 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_lload_2(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[2];
  uint32_t high = vm->current_frame->local_variable[2 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_lload_3(struct vm * vm)
{
  uint32_t low = vm->current_frame->local_variable[3];
  uint32_t high = vm->current_frame->local_variable[3 + 1];
  operand_stack_push_u32(vm->current_frame, low);
  operand_stack_push_u32(vm->current_frame, high);
}

void op_lmul(struct vm * vm)
{
  int64_t value2 = operand_stack_pop_u64(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int64_t result = value1 * value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lneg(struct vm * vm)
{
  int64_t value = operand_stack_pop_u64(vm->current_frame);
  int64_t result = -value;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lookupswitch(struct vm * vm, int32_t defaultbyte, int32_t npairs, const int32_t * table)
{
  int32_t key = operand_stack_pop_u32(vm->current_frame);
  for (int i = 0; i < npairs; i++) {
    int32_t match = BE_BSWAP32(table[i * 2]);
    if (key == match) {
      int32_t offset = BE_BSWAP32(table[i * 2 + 1]);
      vm->current_frame->next_pc = vm->current_frame->pc + offset;
      return;
    }
  }
  vm->current_frame->next_pc = vm->current_frame->pc + defaultbyte;
}

void op_lor(struct vm * vm)
{
  uint64_t value2 = operand_stack_pop_u64(vm->current_frame);
  uint64_t value1 = operand_stack_pop_u64(vm->current_frame);
  uint64_t result = value1 | value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lrem(struct vm * vm)
{
  int64_t value2 = operand_stack_pop_u64(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int64_t result = value1 % value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lreturn(struct vm * vm)
{
  assert(vm->current_frame->return_type == 'J');
  vm_method_return(vm);
}

void op_lshl(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int s = value2 & 0b111111;
  int64_t result = value1 << s;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lshr(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int s = value2 & 0b111111;
  int64_t result = value1 >> s;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lstore(struct vm * vm, uint32_t index)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[index + 1] = high;
  vm->current_frame->local_variable[index] = low;
}

void op_lstore_0(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[0 + 1] = high;
  vm->current_frame->local_variable[0] = low;
}

void op_lstore_1(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[1 + 1] = high;
  vm->current_frame->local_variable[1] = low;
}

void op_lstore_2(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[2 + 1] = high;
  vm->current_frame->local_variable[2] = low;
}

void op_lstore_3(struct vm * vm)
{
  uint32_t high = operand_stack_pop_u32(vm->current_frame);
  uint32_t low = operand_stack_pop_u32(vm->current_frame);
  vm->current_frame->local_variable[3 + 1] = high;
  vm->current_frame->local_variable[3] = low;
}

void op_lsub(struct vm * vm)
{
  int64_t value2 = operand_stack_pop_u64(vm->current_frame);
  int64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int64_t result = value1 - value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lushr(struct vm * vm)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint64_t value1 = operand_stack_pop_u64(vm->current_frame);
  int s = value2 & 0b111111;
  uint64_t result = value1 >> s;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_lxor(struct vm * vm)
{
  uint64_t value2 = operand_stack_pop_u64(vm->current_frame);
  uint64_t value1 = operand_stack_pop_u64(vm->current_frame);
  uint64_t result = value1 ^ value2;
  operand_stack_push_u64(vm->current_frame, result);
}

void op_monitorenter(struct vm * vm)
{
  assert(!"op_monitorenter");
}

void op_monitorexit(struct vm * vm)
{
  assert(!"op_monitorexit");
}

static int32_t * _multiarray(int32_t * dims, int num_dimensions, int level, uint8_t * type)
{
  int32_t count = dims[level];
  int32_t element_size = field_size_array(*type);
  int32_t size = element_size * count + 4;
  int32_t * arrayref = memory_allocate(size);
  assert(arrayref != nullptr);
  arrayref[0] = count;

  int32_t u32_count = (size - 4 + 3) / 4;
  for (int i = 0; i < u32_count; i++) {
    if (level == num_dimensions - 1) {
      arrayref[i + 1] = 0;
    } else {
      assert(*type == '[');
      arrayref[1 + i] = (int32_t)_multiarray(dims, num_dimensions, level + 1, type + 1);
    }
  }
  return arrayref;
}

void op_multianewarray(struct vm * vm, uint32_t index, uint32_t dimensions)
{
  struct constant * class_constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  assert(class_constant->tag == CONSTANT_Class);
  struct constant * type_constant = &vm->current_frame->class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  assert(type_constant->tag == CONSTANT_Utf8);

  // The run-time constant pool entry at the index must be a symbolic reference
  // to a class, array, or interface type
  uint8_t * type = type_constant->utf8.bytes;
  assert(*type == '[');

  assert(dimensions > 0);
  int32_t dims[dimensions];
  for (int i = 0; i < dimensions; i++) {
    dims[dimensions - i - 1] = operand_stack_pop_u32(vm->current_frame);
  }
  int32_t * arrayref = _multiarray(dims, dimensions, 0, type + 1);
  operand_stack_push_u32(vm->current_frame, (uint32_t)arrayref);
}

void op_new(struct vm * vm, uint32_t index)
{
  struct constant * class_constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * class_name_constant = &vm->current_frame->class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif

  struct class_entry * class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                                                 vm->class_hash_table.entry,
                                                                 class_name_constant->utf8.bytes,
                                                                 class_name_constant->utf8.length);
  assert(class_entry != nullptr);

  /* On successful resolution of the class, it is initialized if it has not
     already been initialized (§5.5).

     (new) Upon execution of a new instruction, the class to be initialized is
     the class referenced by the instruction. */

  if (!vm_initialize_class(vm, class_entry))
    return;

  /* Memory for a new instance of that class is allocated from the
     garbage-collected heap, and the instance variables of the new object are
     initialized to their default initial values (§2.3, §2.4). The objectref, a
     reference to the instance, is pushed onto the operand stack. */

  int fields_count = class_entry->instance_fields_count;
  int32_t * objectref = memory_allocate(fields_count * 2 * 4 + 4);
  assert(objectref != nullptr);
  objectref[0] = (int32_t)class_entry;
  int32_t * objectfields = &objectref[1];
  for (int i = 0; i < fields_count; i++) {
    objectfields[i * 2] = 0;
    objectfields[i * 2 + 1] = 0;
  }

  operand_stack_push_u32(vm->current_frame, (uint32_t)objectref);
}

enum ARRAY_TYPE {
  T_BOOLEAN = 4, // 1 byte
  T_CHAR = 5, // 2 bytes
  T_FLOAT = 6, // 4 bytes
  T_DOUBLE = 7, // 8 bytes
  T_BYTE = 8, // 1 byte
  T_SHORT = 9, // 2 bytes
  T_INT = 10, // 4 bytes
  T_LONG = 11, // 8 bytes
};

void op_newarray(struct vm * vm, uint32_t atype)
{
  int32_t element_size = 0;
  switch (atype) {
  case T_BOOLEAN: [[fallthrough]]; // 1 byte
  case T_BYTE:                     // 1 byte
    element_size = 1;
    break;
  case T_CHAR:    [[fallthrough]]; // 2 bytes
  case T_SHORT:                    // 2 bytes
    element_size = 2;
    break;
  case T_FLOAT:   [[fallthrough]]; // 4 bytes
  case T_INT:                      // 4 bytes
    element_size = 4;
    break;
  case T_DOUBLE:  [[fallthrough]]; // 8 bytes
  case T_LONG:                     // 8 bytes
    element_size = 8;
    break;
  default:
    assert(false);
    break;
  }
  int32_t count = operand_stack_pop_u32(vm->current_frame);
  int32_t size = element_size * count + 4;
  int32_t * arrayref = memory_allocate(size);
  assert(arrayref != nullptr);
  arrayref[0] = count;

  /* Each of the elements of the new array is initialized to the default initial
     value (§2.3, §2.4) for the element type of the array type. */
  /* round up u32_count, possibly initializing past the end of the array. This
     is acceptable because memory_allocate always allocates a multiple of 4
     greater than or equal to `size`. */
  int32_t u32_count = (size - 4 + 3) / 4;
  for (int i = 0; i < u32_count; i++) {
    arrayref[i + 1] = 0;
  }

  operand_stack_push_u32(vm->current_frame, (uint32_t)arrayref);
}

void op_nop(struct vm * vm)
{
}

void op_pop(struct vm * vm)
{
  operand_stack_pop_u32(vm->current_frame);
}

void op_pop2(struct vm * vm)
{
  operand_stack_pop_u32(vm->current_frame);
  operand_stack_pop_u32(vm->current_frame);
}

void op_putfield(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct field_entry * field_entry;
  struct constant * field_descriptor_constant;
  class_entry_field_entry_from_constant_index(vm,
                                              index,
                                              &class_entry,
                                              &field_entry,
                                              &field_descriptor_constant);

  /* The type of a value stored by a putfield instruction must be compatible
     with the descriptor of the referenced field (§4.3.2). If the field descriptor
     type is boolean, byte, char, short, or int, then the value must be an int. If
     the field descriptor type is float, long, or double, then the value must be a
     float, long, or double, respectively. If the field descriptor type is a class
     type or an array type, then the value must be a value of the field descriptor
     type. */

  debugf("putfield instance_index %d\n", field_entry->instance_index);

  switch (field_descriptor_constant->utf8.bytes[0]) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    {
      uint32_t value = operand_stack_pop_u32(vm->current_frame);
      int32_t * objectref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
      assert(objectref != nullptr);
      int32_t * objectfields = &objectref[1];
      objectfields[field_entry->instance_index] = value;
    }
    break;
  case 'D': [[fallthrough]];
  case 'J':
    {
      uint32_t high = operand_stack_pop_u32(vm->current_frame);
      uint32_t low = operand_stack_pop_u32(vm->current_frame);
      int32_t * objectref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
      assert(objectref != nullptr);
      int32_t * objectfields = &objectref[1];
      objectfields[field_entry->instance_index + 1] = high;
      objectfields[field_entry->instance_index] = low;
    }
    break;
  default:
    assert(false);
  }
}

void op_putstatic(struct vm * vm, uint32_t index)
{
  struct class_entry * class_entry;
  struct field_entry * field_entry;
  struct constant * field_descriptor_constant;
  class_entry_field_entry_from_constant_index(vm, index,
                                              &class_entry,
                                              &field_entry,
                                              &field_descriptor_constant);

  /* The type of a value stored by a putstatic instruction must be compatible
     with the descriptor of the referenced field (§4.3.2). If the field
     descriptor type is boolean, byte, char, short, or int, then the value must
     be an int. If the field descriptor type is float, long, or double, then the
     value must be a float, long, or double, respectively. If the field
     descriptor type is a class type or an array type, then the value must be a
     value of the field descriptor type. */

  /* On successful resolution of the field, the class or interface that declared
     the resolved field is initialized if that class or interface has not
     already been initialized (§5.5). */

  if (!vm_initialize_class(vm, class_entry))
    return;

  switch (field_descriptor_constant->utf8.bytes[0]) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    {
      uint32_t value = operand_stack_pop_u32(vm->current_frame);
      class_entry->static_fields[field_entry->static_index] = value;
    }
    break;
  case 'D': [[fallthrough]];
  case 'J':
    {
      uint32_t high = operand_stack_pop_u32(vm->current_frame);
      uint32_t low = operand_stack_pop_u32(vm->current_frame);
      class_entry->static_fields[field_entry->static_index + 1] = high;
      class_entry->static_fields[field_entry->static_index] = low;
    }
    break;
  default:
    assert(false);
  }
}

void op_ret(struct vm * vm, uint32_t index)
{
  assert(!"op_ret");
}

void op_return(struct vm * vm)
{
  vm_method_return(vm);
}

void op_saload(struct vm * vm)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int16_t * shortarray = (int16_t *)&arrayref[1];
  int16_t value = shortarray[index];
  operand_stack_push_u32(vm->current_frame, value);
}

void op_sastore(struct vm * vm)
{
  uint16_t value = operand_stack_pop_u32(vm->current_frame);
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  int32_t * arrayref = (int32_t *)operand_stack_pop_u32(vm->current_frame);
  assert(arrayref[0] > 0 && index < arrayref[0]);
  int16_t * shortarray = (int16_t *)&arrayref[1];
  shortarray[index] = value;
}

void op_sipush(struct vm * vm, int32_t byte)
{
  operand_stack_push_u32(vm->current_frame, byte);
}

void op_swap(struct vm * vm)
{
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  operand_stack_push_u32(vm->current_frame, value1);
  operand_stack_push_u32(vm->current_frame, value2);
}

void op_tableswitch(struct vm * vm, int32_t defaultbyte, int32_t lowbyte, int32_t highbyte, const int32_t * table)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  if (index < lowbyte || index > highbyte) {
    vm->current_frame->next_pc = vm->current_frame->pc + defaultbyte;
  } else {
    int32_t offset = BE_BSWAP32(table[index - lowbyte]);
    vm->current_frame->next_pc = vm->current_frame->pc + offset;
  }
}
