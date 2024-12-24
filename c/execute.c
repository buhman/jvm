#include <stdio.h>

#include "execute.h"
#include "memory_allocator.h"
#include "bswap.h"
#include "class_resolver.h"

void op_aaload(struct vm * vm)
{
  assert(!"op_aaload");
}

void op_aastore(struct vm * vm)
{
  assert(!"op_aastore");
}

void op_aconst_null(struct vm * vm)
{
  assert(!"op_aconst_null");
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
  assert(!"op_anewarray");
}

void op_areturn(struct vm * vm)
{
  assert(!"op_areturn");
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
  printf("op_astore0 %d\n", vm->current_frame->operand_stack_ix);
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
  assert(!"op_baload");
}

void op_bastore(struct vm * vm)
{
  assert(!"op_bastore");
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
  assert(!"op_d2f");
}

void op_d2i(struct vm * vm)
{
  assert(!"op_d2i");
}

void op_d2l(struct vm * vm)
{
  assert(!"op_d2l");
}

void op_dadd(struct vm * vm)
{
  assert(!"op_dadd");
}

void op_daload(struct vm * vm)
{
  assert(!"op_daload");
}

void op_dastore(struct vm * vm)
{
  assert(!"op_dastore");
}

void op_dcmpg(struct vm * vm)
{
  assert(!"op_dcmpg");
}

void op_dcmpl(struct vm * vm)
{
  assert(!"op_dcmpl");
}

void op_dconst_0(struct vm * vm)
{
  assert(!"op_dconst_0");
}

void op_dconst_1(struct vm * vm)
{
  assert(!"op_dconst_1");
}

void op_ddiv(struct vm * vm)
{
  assert(!"op_ddiv");
}

void op_dload(struct vm * vm, uint32_t index)
{
  assert(!"op_dload");
}

void op_dload_0(struct vm * vm)
{
  assert(!"op_dload_0");
}

void op_dload_1(struct vm * vm)
{
  assert(!"op_dload_1");
}

void op_dload_2(struct vm * vm)
{
  assert(!"op_dload_2");
}

void op_dload_3(struct vm * vm)
{
  assert(!"op_dload_3");
}

void op_dmul(struct vm * vm)
{
  assert(!"op_dmul");
}

void op_dneg(struct vm * vm)
{
  assert(!"op_dneg");
}

void op_drem(struct vm * vm)
{
  assert(!"op_drem");
}

void op_dreturn(struct vm * vm)
{
  assert(!"op_dreturn");
}

void op_dstore(struct vm * vm, uint32_t index)
{
  assert(!"op_dstore");
}

void op_dstore_0(struct vm * vm)
{
  assert(!"op_dstore_0");
}

void op_dstore_1(struct vm * vm)
{
  assert(!"op_dstore_1");
}

void op_dstore_2(struct vm * vm)
{
  assert(!"op_dstore_2");
}

void op_dstore_3(struct vm * vm)
{
  assert(!"op_dstore_3");
}

void op_dsub(struct vm * vm)
{
  assert(!"op_dsub");
}

void op_dup(struct vm * vm)
{
  operand_stack_dup_u32(vm->current_frame);
}

void op_dup2(struct vm * vm)
{
  assert(!"op_dup2");
}

void op_dup2_x1(struct vm * vm)
{
  assert(!"op_dup2_x1");
}

void op_dup2_x2(struct vm * vm)
{
  assert(!"op_dup2_x2");
}

void op_dup_x1(struct vm * vm)
{
  assert(!"op_dup_x1");
}

void op_dup_x2(struct vm * vm)
{
  assert(!"op_dup_x2");
}

void op_f2d(struct vm * vm)
{
  assert(!"op_f2d");
}

void op_f2i(struct vm * vm)
{
  float value = operand_stack_pop_f32(vm->current_frame);
  int32_t result = (int32_t)value;
  operand_stack_push_u32(vm->current_frame, result);
}

void op_f2l(struct vm * vm)
{
  assert(!"op_f2l");
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
  assert(!"op_getfield");
}

void op_getstatic(struct vm * vm, uint32_t index)
{
  struct constant * fieldref_constant = &vm->current_thread.current_class->constant_pool[index - 1];
  #ifdef DEBUG
  assert(fieldref_constant->tag == CONSTANT_Fieldref);
  #endif
  struct constant * class_constant = &vm->current_thread.current_class->constant_pool[fieldref_constant->fieldref.class_index - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * nameandtype_constant = &vm->current_thread.current_class->constant_pool[fieldref_constant->fieldref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  struct constant * class_name_constant = &vm->current_thread.current_class->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif
  struct constant * field_name_constant = &vm->current_thread.current_class->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  #ifdef DEBUG
  assert(field_name_constant->tag == CONSTANT_Utf8);
  #endif

  struct class_entry * class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                                                 vm->class_hash_table.entry,
                                                                 class_name_constant->utf8.bytes,
                                                                 class_name_constant->utf8.length);
  assert(class_entry != nullptr);

  struct field_entry * field_entry = class_resolver_lookup_field(class_entry,
                                                                 field_name_constant->utf8.bytes,
                                                                 field_name_constant->utf8.length);
  assert(field_entry != nullptr);

  uint32_t value = field_entry->value;
  operand_stack_push_u32(vm->current_frame, value);
}

void op_goto(struct vm * vm, int32_t branch)
{
  vm->current_frame->pc = vm->current_frame->pc + branch;
}

void op_goto_w(struct vm * vm, int32_t branch)
{
  assert(!"op_goto_w");
}

void op_i2b(struct vm * vm)
{
  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  uint8_t result = value;
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
  assert(!"op_i2d");
}

void op_i2f(struct vm * vm)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  float result = (float)value;
  operand_stack_push_f32(vm->current_frame, result);
}

void op_i2l(struct vm * vm)
{
  assert(!"op_i2l");
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
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 & value2;
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
  assert(!"op_if_acmpeq");
}

void op_if_acmpne(struct vm * vm, int32_t branch)
{
  assert(!"op_if_acmpne");
}

void op_if_icmpeq(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 == value2) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpge(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 >= value2) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpgt(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 > value2) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmple(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 <= value2) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmplt(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 < value2) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_if_icmpne(struct vm * vm, int32_t branch)
{
  int32_t value2 = operand_stack_pop_u32(vm->current_frame);
  int32_t value1 = operand_stack_pop_u32(vm->current_frame);
  if (value1 != value2) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifeq(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value == 0) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifge(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value >= 0) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifgt(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value > 0) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifle(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value <= 0) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_iflt(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value < 0) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifne(struct vm * vm, int32_t branch)
{
  int32_t value = operand_stack_pop_u32(vm->current_frame);
  if (value != 0) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifnonnull(struct vm * vm, int32_t branch)
{
  void * value = (void *)operand_stack_pop_u32(vm->current_frame);
  if (value != nullptr) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_ifnull(struct vm * vm, int32_t branch)
{
  void * value = (void *)operand_stack_pop_u32(vm->current_frame);
  if (value == nullptr) {
    vm->current_frame->pc = vm->current_frame->pc + branch;
  }
}

void op_iinc(struct vm * vm, uint32_t index, uint32_t _const)
{
  uint32_t value = vm->current_frame->local_variable[index];
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
  assert(!"op_instanceof");
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
  assert(!"op_invokespecial");
}

void op_invokestatic(struct vm * vm, uint32_t index)
{
  struct constant * methodref_constant = &vm->current_thread.current_class->constant_pool[index - 1];
  #ifdef DEBUG
  assert(methodref_constant->tag == CONSTANT_Methodref);
  #endif
  struct constant * class_constant = &vm->current_thread.current_class->constant_pool[methodref_constant->methodref.class_index - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * nameandtype_constant = &vm->current_thread.current_class->constant_pool[methodref_constant->methodref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  struct constant * class_name_constant = &vm->current_thread.current_class->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif
  struct constant * method_name_constant = &vm->current_thread.current_class->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  #ifdef DEBUG
  assert(method_name_constant->tag == CONSTANT_Utf8);
  #endif

  struct class_entry * class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                                                 vm->class_hash_table.entry,
                                                                 class_name_constant->utf8.bytes,
                                                                 class_name_constant->utf8.length);
  assert(class_entry != nullptr);

  struct method_info * method_info = class_resolver_lookup_method(class_entry,
                                                                  method_name_constant->utf8.bytes,
                                                                  method_name_constant->utf8.length);
  assert(method_info != nullptr);

  vm_static_method_call(vm, class_entry->class_file, method_info);
}

void op_invokevirtual(struct vm * vm, uint32_t index)
{
  assert(!"op_invokevirtual");
}

void op_ior(struct vm * vm)
{
  uint32_t value2 = operand_stack_pop_u32(vm->current_frame);
  uint32_t value1 = operand_stack_pop_u32(vm->current_frame);
  int32_t result = value1 | value2;
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

  uint32_t value = operand_stack_pop_u32(vm->current_frame);
  switch (vm->current_frame->return_type) {
  case 'I':
    break;
  default:
    fprintf(stderr, "conversion not implemented: %c\n", vm->current_frame->return_type);
    assert(false);
    break;
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
  int32_t result = value1 ^ value2;
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
  assert(!"op_l2d");
}

void op_l2f(struct vm * vm)
{
  assert(!"op_l2f");
}

void op_l2i(struct vm * vm)
{
  assert(!"op_l2i");
}

void op_ladd(struct vm * vm)
{
  assert(!"op_ladd");
}

void op_laload(struct vm * vm)
{
  assert(!"op_laload");
}

void op_land(struct vm * vm)
{
  assert(!"op_land");
}

void op_lastore(struct vm * vm)
{
  assert(!"op_lastore");
}

void op_lcmp(struct vm * vm)
{
  assert(!"op_lcmp");
}

void op_lconst_0(struct vm * vm)
{
  assert(!"op_lconst_0");
}

void op_lconst_1(struct vm * vm)
{
  assert(!"op_lconst_1");
}

void op_ldc(struct vm * vm, uint32_t index)
{
  struct constant * constant = &vm->current_thread.current_class->constant_pool[index - 1];
  #ifdef DEBUG
  assert(constant->tag == CONSTANT_Integer || constant->tag == CONSTANT_Float);
  #endif
  int32_t value = constant->integer.bytes;
  operand_stack_push_u32(vm->current_frame, value);
}

void op_ldc2_w(struct vm * vm, uint32_t index)
{
  assert(!"op_ldc2_w");
}

void op_ldc_w(struct vm * vm, uint32_t index)
{
  assert(!"op_ldc_w");
}

void op_ldiv(struct vm * vm)
{
  assert(!"op_ldiv");
}

void op_lload(struct vm * vm, uint32_t index)
{
  assert(!"op_lload");
}

void op_lload_0(struct vm * vm)
{
  assert(!"op_lload_0");
}

void op_lload_1(struct vm * vm)
{
  assert(!"op_lload_1");
}

void op_lload_2(struct vm * vm)
{
  assert(!"op_lload_2");
}

void op_lload_3(struct vm * vm)
{
  assert(!"op_lload_3");
}

void op_lmul(struct vm * vm)
{
  assert(!"op_lmul");
}

void op_lneg(struct vm * vm)
{
  assert(!"op_lneg");
}

void op_lookupswitch(struct vm * vm)
{
  assert(!"op_lookupswitch");
}

void op_lor(struct vm * vm)
{
  assert(!"op_lor");
}

void op_lrem(struct vm * vm)
{
  assert(!"op_lrem");
}

void op_lreturn(struct vm * vm)
{
  assert(!"op_lreturn");
}

void op_lshl(struct vm * vm)
{
  assert(!"op_lshl");
}

void op_lshr(struct vm * vm)
{
  assert(!"op_lshr");
}

void op_lstore(struct vm * vm, uint32_t index)
{
  assert(!"op_lstore");
}

void op_lstore_0(struct vm * vm)
{
  assert(!"op_lstore_0");
}

void op_lstore_1(struct vm * vm)
{
  assert(!"op_lstore_1");
}

void op_lstore_2(struct vm * vm)
{
  assert(!"op_lstore_2");
}

void op_lstore_3(struct vm * vm)
{
  assert(!"op_lstore_3");
}

void op_lsub(struct vm * vm)
{
  assert(!"op_lsub");
}

void op_lushr(struct vm * vm)
{
  assert(!"op_lushr");
}

void op_lxor(struct vm * vm)
{
  assert(!"op_lxor");
}

void op_monitorenter(struct vm * vm)
{
  assert(!"op_monitorenter");
}

void op_monitorexit(struct vm * vm)
{
  assert(!"op_monitorexit");
}

void op_multianewarray(struct vm * vm, uint32_t index, uint32_t dimensions)
{
  assert(!"op_multianewarray");
}

void op_new(struct vm * vm, uint32_t index)
{
  assert(!"op_new");
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
  assert(arrayref != 0);
  arrayref[0] = count;
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
  assert(!"op_pop2");
}

void op_putfield(struct vm * vm, uint32_t index)
{
  assert(!"op_putfield");
}

void op_putstatic(struct vm * vm, uint32_t index)
{
  assert(!"op_putstatic");
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
  assert(!"op_saload");
}

void op_sastore(struct vm * vm)
{
  assert(!"op_sastore");
}

void op_sipush(struct vm * vm, int32_t byte)
{
  assert(!"op_sipush2");
}

void op_swap(struct vm * vm)
{
  assert(!"op_swap");
}

void op_tableswitch(struct vm * vm, int32_t defaultbyte, int32_t lowbyte, int32_t highbyte, const int32_t * table)
{
  int32_t index = operand_stack_pop_u32(vm->current_frame);
  if (index < lowbyte || index > highbyte) {
    vm->current_frame->pc = vm->current_frame->pc + defaultbyte;
  } else {
    int32_t offset = BE_BSWAP32(table[index - lowbyte]);
    vm->current_frame->pc = vm->current_frame->pc + offset;
  }
}

void op_wide(struct vm * vm)
{
  assert(!"op_wide");
}
