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

int find_constantvalue_name_index(struct class_file * class_file)
{
  for (int i = 0; i < class_file->constant_pool_count; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    if (constant->tag == CONSTANT_Utf8) {
      if (bytes_equal(constant->utf8.length, constant->utf8.bytes, "ConstantValue")) {
        return i + 1;
      }
    }
  }
  return 0;
}

static int descriptor_nargs(struct constant * descriptor_constant, uint8_t * return_type)
{
  assert(descriptor_constant->tag == CONSTANT_Utf8);
  assert(descriptor_constant->utf8.length >= 2);
  assert(descriptor_constant->utf8.bytes[0] == '(');

  printf("method descriptor: ");
  print_utf8_string(descriptor_constant);
  printf("\n");

  int i = 1;
  int nargs = 0;
  while (i < descriptor_constant->utf8.length) {
    uint8_t byte = descriptor_constant->utf8.bytes[i];
    if (byte == ')')
      break;
    switch (byte) {
    case '[':
      break;
    case 'D': [[fallthrough]];
    case 'J':
      nargs += 2;
      break;
    case 'L':
      nargs += 1;
      while (descriptor_constant->utf8.bytes[i] != ';') i += 1;
      break;
    default:
      nargs += 1;
      break;
    }
    i += 1;
  }

  *return_type = descriptor_constant->utf8.bytes[i + 1];

  return nargs;
}

bool vm_initialize_class(struct vm * vm, struct class_entry * class_entry)
{
  printf("vm_initialize_class: ");
  struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif
  print_constant(class_name_constant);
  printf("\n");

  if (class_entry->initialization_state == CLASS_INITIALIZED)
    return true;

  if (class_entry->initialization_state == CLASS_INITIALIZING) {
    if (vm->current_frame->class_entry->class_file == class_entry->class_file)
      return true;
    else
      assert(false); // possible infinite initialization loop
  }

  class_entry->initialization_state = CLASS_INITIALIZING;

  /* Then, initialize each static field of C with the constant value in its
     ConstantValue attribute (§4.7.2), in the order the fields appear in the
     ClassFile structure. */

  struct class_file * class_file = class_entry->class_file;

  int constantvalue_name_index = find_constantvalue_name_index(class_file);
  if (constantvalue_name_index != 0) {
    for (int i = 0; i < class_file->fields_count; i++) {
      struct field_info * field_info = &class_file->fields[i];
      if (!(field_info->access_flags & FIELD_ACC_STATIC))
        continue;

      for (int j = 0; j < field_info->attributes_count; j++) {
        if (field_info->attributes[j].attribute_name_index == constantvalue_name_index) {
          struct attribute_info * attribute = &field_info->attributes[j];
          struct constant * constantvalue = &class_file->constant_pool[attribute->constantvalue->constantvalue_index - 1];
          assert(constantvalue->tag == CONSTANT_Integer); // also need to support CONSTANT_String

          struct constant * name_constant = &class_file->constant_pool[field_info->name_index - 1];
          assert(name_constant->tag == CONSTANT_Utf8);
          struct field_entry * field_entry = class_resolver_lookup_field(class_entry,
                                                                         name_constant->utf8.bytes,
                                                                         name_constant->utf8.length);
          assert(field_entry != nullptr);
          field_entry->value32 = constantvalue->integer.bytes;
          printf("  constantvalue: %d\n", field_entry->value32);
          break;
        }
      }
    }
  }

  /* Next, if C declares a class or interface initialization method, execute
     that method. */
  const uint8_t * method_name = (const uint8_t *)"<clinit>";
  int method_name_length = 8;
  const uint8_t * method_descriptor = (const uint8_t *)"()V";
  int method_descriptor_length = 3;

  struct method_info * method_info = class_resolver_lookup_method(class_entry,
                                                                  method_name,
                                                                  method_name_length,
                                                                  method_descriptor,
                                                                  method_descriptor_length);
  if (method_info != nullptr) {
    assert((method_info->access_flags & METHOD_ACC_STATIC) != 0);
    printf("<clinit>\n");

    // tamper with next_pc
    vm->current_frame->next_pc = vm->current_frame->pc;

    vm_static_method_call(vm, class_entry, method_info);

    vm->current_frame->initialization_frame = 1;
    return false;
  } else {
    class_entry->initialization_state = CLASS_INITIALIZED;
    printf("<clinit> does not exist for this class\n");
  }

  return true;
}

void vm_special_method_call(struct vm * vm, struct class_entry * class_entry, struct method_info * method_info)
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

  int code_name_index = find_code_name_index(class_entry->class_file);
  assert(code_name_index > 0);

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
  vm->current_frame->initialization_frame = 0;

  struct constant * descriptor_constant = &class_entry->class_file->constant_pool[method_info->descriptor_index - 1];
  int nargs = descriptor_nargs(descriptor_constant, &vm->current_frame->return_type);
  nargs += 1;
  printf("nargs+1: %d\n", nargs);
  for (int i = 0; i < nargs; i++) {
    uint32_t value = operand_stack_pop_u32(old_frame);
    printf("local[%d] = %x\n", nargs - i - 1, value);
    vm->current_frame->local_variable[nargs - i - 1] = value;
  }

  vm->current_frame->pc = 0;
  vm->current_frame->class_entry = class_entry;
  vm->current_frame->method = method_info;

  printf("operand_stack_ix: %d\n", vm->current_frame->operand_stack_ix);
}

void vm_static_method_call(struct vm * vm, struct class_entry * class_entry, struct method_info * method_info)
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

  int code_name_index = find_code_name_index(class_entry->class_file);
  assert(code_name_index > 0);

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
  vm->current_frame->initialization_frame = 0;

  struct constant * descriptor_constant = &class_entry->class_file->constant_pool[method_info->descriptor_index - 1];
  int nargs = descriptor_nargs(descriptor_constant, &vm->current_frame->return_type);
  printf("nargs %d\n", nargs);
  for (int i = 0; i < nargs; i++) {
    uint32_t value = operand_stack_pop_u32(old_frame);
    printf("local[%d] = %x\n", nargs - i - 1, value);
    vm->current_frame->local_variable[nargs - i - 1] = value;
  }
  ;

  vm->current_frame->pc = 0;
  vm->current_frame->class_entry = class_entry;
  vm->current_frame->method = method_info;

  printf("operand_stack_ix: %d\n", vm->current_frame->operand_stack_ix);
}

void vm_method_return(struct vm * vm)
{
  if (vm->current_frame->initialization_frame != 0) {
    printf("vm_method_return: initialization_frame!=0\n");
    vm->current_frame->class_entry->initialization_state = CLASS_INITIALIZED;
    vm->current_frame->initialization_frame = 0;
  }

  struct frame * old_frame = vm->current_frame;

  stack_pop_data(&vm->data_stack, old_frame->code->max_locals);
  stack_pop_data(&vm->data_stack, old_frame->code->max_stack);

  vm->current_frame = stack_pop_frame(&vm->frame_stack, 1);
  assert(vm->current_frame != old_frame);
  vm->current_frame->pc = vm->current_frame->next_pc;

  /*
    boolean int 1
    byte int 1
    char int 1
    short int 1
    int int 1
    float float 1
    reference reference 1
    returnAddress returnAddress 1
    long long 2
    double double 2
  */
  /*
    B byte
    C char
    D double
    F float
    I int
    J long
    L ClassName ; Named class or interface type
    S short
    Z boolean
    [ ComponentType Array of given component type
  */

  switch (old_frame->return_type) {
  case 'B': [[fallthrough]];
  case 'C': [[fallthrough]];
  case 'F': [[fallthrough]];
  case 'I': [[fallthrough]];
  case 'L': [[fallthrough]];
  case 'S': [[fallthrough]];
  case 'Z': [[fallthrough]];
  case '[':
    {
      uint32_t value = operand_stack_pop_u32(old_frame);
      operand_stack_push_u32(vm->current_frame, value);
    }
    break;
  case 'D': [[fallthrough]];
  case 'J':
    {
      uint64_t value = operand_stack_pop_u64(old_frame);
      operand_stack_push_u64(vm->current_frame, value);
    }
    break;
  case 'V':
    break;
  default:
    fprintf(stderr, "return type not implemented: %c\n", old_frame->return_type);
    assert(false);
    break;
  }
  assert(old_frame->operand_stack_ix == 0);
  printf("vm_method_return\n");
}

static void print_vm_stack(struct vm * vm)
{
  printf("[  ");
  for (int i = 5; i > 0; i--) {
    if (i > vm->current_frame->operand_stack_ix) {
      printf("            ");
      continue;
    }
    int32_t value = vm->current_frame->operand_stack[vm->current_frame->operand_stack_ix - i];
    if (value > 32767 || value < -32768)
      printf("0x%08x  ", value);
    else
      printf("%10d  ", value);
  }
  printf("]\n");
}

void vm_execute(struct vm * vm)
{
  while (true) {
    assert(vm->current_frame->pc < vm->current_frame->code->code_length);
    print_vm_stack(vm);
    decode_print_instruction(vm->current_frame->code->code, vm->current_frame->pc);
    uint32_t old_pc = vm->current_frame->pc;
    struct method_info * old_method = vm->current_frame->method;
    decode_execute_instruction(vm, vm->current_frame->code->code, vm->current_frame->pc);
    if (vm->frame_stack.ix == 1) {
      printf("terminate\n");
      break;
    }
    if (vm->current_frame->method == old_method && vm->current_frame->pc == old_pc) {
      // if the instruction did not branch, increment pc
      vm->current_frame->pc = vm->current_frame->next_pc;
    }
  }
}
