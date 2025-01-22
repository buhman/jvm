#include <stdint.h>

#include "assert.h"
#include "class_file.h"
#include "bytes.h"
#include "decode.h"
#include "class_resolver.h"
#include "printf.h"
#include "string.h"
#include "fatal.h"
#include "debug.h"
#include "find_attribute.h"
#include "backtrace.h"
#include "native_types.h"
#include "native_types_allocate.h"

int descriptor_nargs(struct constant * descriptor_constant, uint8_t * return_type)
{
  assert(descriptor_constant->tag == CONSTANT_Utf8);
  assert(descriptor_constant->utf8.length >= 2);
  assert(descriptor_constant->utf8.bytes[0] == '(');

  debugf("method descriptor: ");
  debug_print__constant__utf8_string(descriptor_constant);
  debugf("\n");

  int i = 1;
  int nargs = 0;
  while (i < descriptor_constant->utf8.length) {
    uint8_t byte = descriptor_constant->utf8.bytes[i];
    if (byte == ')')
      break;
    switch (byte) {
    case '[':
      break;
    case 'D': /* fall through */;
    case 'J':
      nargs += 2;
      break;
    case 'L':
      nargs += 1;
      while (descriptor_constant->utf8.bytes[i] != ';') i += 1;
      break;
    case 'B': /* fall through */;
    case 'C': /* fall through */;
    case 'F': /* fall through */;
    case 'I': /* fall through */;
    case 'S': /* fall through */;
    case 'Z':
      nargs += 1;
      break;
    default:
      assert(false);
      break;
    }
    i += 1;
  }

  *return_type = descriptor_constant->utf8.bytes[i + 1];

  return nargs;
}

bool vm_initialize_class(struct vm * vm, struct class_entry * class_entry)
{
  debugf("vm_initialize_class: ");
  struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif
  debug_print__constant__utf8_string(class_name_constant);
  debugf("\n");

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
          struct constant * name_constant = &class_file->constant_pool[field_info->name_index - 1];
          assert(name_constant->tag == CONSTANT_Utf8);
          struct field_entry * field_entry = class_resolver_lookup_field(class_entry->fields.length,
                                                                         class_entry->fields.entry,
                                                                         name_constant->utf8.bytes,
                                                                         name_constant->utf8.length);
          assert(field_entry != nullptr);

          struct attribute_info * attribute = &field_info->attributes[j];
          struct constant * constantvalue = &class_file->constant_pool[attribute->constantvalue->constantvalue_index - 1];
          if (constantvalue->tag == CONSTANT_Integer) {
            class_entry->static_fields[field_entry->static_index] = constantvalue->integer.bytes;
          } else if (constantvalue->tag == CONSTANT_String) {
            struct objectref * objectref = class_resolver_lookup_string(vm,
                                                                        class_entry,
                                                                        attribute->constantvalue->constantvalue_index);
            class_entry->static_fields[field_entry->static_index] = (int32_t)objectref;
          } else {
            assert(!"invalid constantvalue tag");
          }
          break;

        }
      }
    }
  }

  /* Next, if C declares a class or interface initialization method, execute
     that method. */
  const uint8_t * method_name = (const uint8_t *)"<clinit>";
  int method_name_length = string_length((const char *)method_name);
  const uint8_t * method_descriptor = (const uint8_t *)"()V";
  int method_descriptor_length = string_length((const char *)method_descriptor);

  struct method_entry method_entry =
    class_resolver_lookup_method_from_method_name_method_descriptor(class_entry,
                                                                    method_name,
                                                                    method_name_length,
                                                                    method_descriptor,
                                                                    method_descriptor_length);

  if (method_entry.method_info != nullptr) {
    assert((method_entry.method_info->access_flags & METHOD_ACC_STATIC) != 0);
    debugf("<clinit>\n");

    // tamper with next_pc
    vm->current_frame->next_pc = vm->current_frame->pc;

    vm_static_method_call(vm, class_entry, &method_entry);

    vm->current_frame->initialization_frame = 1;
    return false;
  } else {
    class_entry->initialization_state = CLASS_INITIALIZED;
    debugf("<clinit> does not exist for this class\n");
  }

  return true;
}

void vm_native_method_call(struct vm * vm, struct class_entry * class_entry, struct method_entry * method_entry, int nargs, uint8_t return_type)
{
  debugf("vm_native_method_call: nargs %d\n", nargs);

  uint32_t args[nargs];
  for (int i = 0; i < nargs; i++) {
    uint32_t value = operand_stack_pop_u32(vm->current_frame);
    debugf("args[%d] = %x\n", nargs - i - 1, value);
    args[nargs - i - 1] = value;
  }

  int old_stack_ix = vm->current_frame->operand_stack_ix;

  method_entry->native_func(vm, args);

  if (return_type != 'V') {
    assert(old_stack_ix == vm->current_frame->operand_stack_ix - 1);
  } else {
    assert(old_stack_ix == vm->current_frame->operand_stack_ix);
  }
}

void vm_method_call(struct vm * vm, struct class_entry * class_entry, struct method_entry * method_entry, int nargs, uint8_t return_type)
{
  assert(method_entry->code_attribute != nullptr);

  struct frame * old_frame = vm->current_frame;

  vm->current_frame = stack_push_frame(&vm->frame_stack, 1);
  vm->current_frame->local_variable = stack_push_data(&vm->data_stack, method_entry->code_attribute->max_locals);
  vm->current_frame->operand_stack = stack_push_data(&vm->data_stack, method_entry->code_attribute->max_stack);
  vm->current_frame->operand_stack_ix = 0;
  vm->current_frame->initialization_frame = 0;
  vm->current_frame->return_type = return_type;

  for (int i = 0; i < nargs; i++) {
    uint32_t value = operand_stack_pop_u32(old_frame);
    debugf("local[%d] = %x\n", nargs - i - 1, value);
    vm->current_frame->local_variable[nargs - i - 1] = value;
  }

  vm->current_frame->pc = 0;
  vm->current_frame->next_pc = 0;
  vm->current_frame->class_entry = class_entry;
  vm->current_frame->method_info = method_entry->method_info;
  vm->current_frame->code_attribute = method_entry->code_attribute;

  debugf("operand_stack_ix: %d\n", vm->current_frame->operand_stack_ix);
}

void vm_special_method_call(struct vm * vm, struct class_entry * class_entry, struct method_entry * method_entry)
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

  uint8_t return_type;
  struct constant * descriptor_constant = &class_entry->class_file->constant_pool[method_entry->method_info->descriptor_index - 1];
  int nargs = descriptor_nargs(descriptor_constant, &return_type);
  nargs += 1;
  debugf("nargs+1: %d\n", nargs);

  if (method_entry->method_info->access_flags & METHOD_ACC_NATIVE) {
    vm_native_method_call(vm, class_entry, method_entry, nargs, return_type);
  } else {
    vm_method_call(vm, class_entry, method_entry, nargs, return_type);
  }
}

void vm_static_method_call(struct vm * vm, struct class_entry * class_entry, struct method_entry * method_entry)
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

  uint8_t return_type;
  struct constant * descriptor_constant = &class_entry->class_file->constant_pool[method_entry->method_info->descriptor_index - 1];
  int nargs = descriptor_nargs(descriptor_constant, &return_type);
  debugf("nargs %d\n", nargs);

  if (method_entry->method_info->access_flags & METHOD_ACC_NATIVE) {
    vm_native_method_call(vm, class_entry, method_entry, nargs, return_type);
  } else {
    vm_method_call(vm, class_entry, method_entry, nargs, return_type);
  }
}

void vm_method_return(struct vm * vm)
{
  if (vm->current_frame->initialization_frame != 0) {
    debugf("vm_method_return: initialization_frame!=0\n");
    vm->current_frame->class_entry->initialization_state = CLASS_INITIALIZED;
    vm->current_frame->initialization_frame = 0;
  }

  struct frame * old_frame = vm->current_frame;

  stack_pop_data(&vm->data_stack, old_frame->code_attribute->max_locals);
  stack_pop_data(&vm->data_stack, old_frame->code_attribute->max_stack);

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
  case 'B': /* fall through */;
  case 'C': /* fall through */;
  case 'F': /* fall through */;
  case 'I': /* fall through */;
  case 'L': /* fall through */;
  case 'S': /* fall through */;
  case 'Z': /* fall through */;
  case '[':
    {
      uint32_t value = operand_stack_pop_u32(old_frame);
      operand_stack_push_u32(vm->current_frame, value);
    }
    break;
  case 'D': /* fall through */;
  case 'J':
    {
      uint64_t value = operand_stack_pop_u64(old_frame);
      operand_stack_push_u64(vm->current_frame, value);
    }
    break;
  case 'V':
    break;
  default:
    debugf("return type not implemented: %c\n", old_frame->return_type);
    assert(false);
    break;
  }
  assert(old_frame->operand_stack_ix == 0);
  #ifdef MAIN_STRING_ARRAY
  if (vm->frame_stack.ix > 1) {
  #else
  if (vm->frame_stack.ix > 0) {
  #endif
    debugs("vm_method_return\n");
    debugs("current_frame:\n  class:  ");
    debug_print__class_file__class_name(vm->current_frame->class_entry->class_file);
    debugs("\n  method: ");
    debug_print__method_info__method_name(vm->current_frame->class_entry->class_file, vm->current_frame->method_info);
    debugf("\n  pc:      %d", vm->current_frame->pc);
    debugf("\n  next_pc: %d\n", vm->current_frame->next_pc);
  }
}

void vm_exception(struct vm * vm, struct objectref * objectref)
{
  // If objectref is null, athrow throws a NullPointerException instead of objectref.
  assert(objectref != nullptr);

  struct class_entry * exception_class_entry = objectref->class_entry;
  if (objectref->oref[0] == nullptr) {
    // FIXME: make backtrace a real objectref
    objectref->oref[0] = (struct objectref *)backtrace_allocate(vm);
  }

  while (vm->frame_stack.ix > 0) {
    for (int i = 0; i < vm->current_frame->code_attribute->exception_table_length; i++) {
      struct exception_table_entry * entry = &vm->current_frame->code_attribute->exception_table[i];
      bool caught =
        vm->current_frame->pc >= entry->start_pc &&
        vm->current_frame->pc < entry->end_pc &&
        exception_class_entry == class_resolver_lookup_class_from_class_index(vm->class_hash_table.length,
                                                                              vm->class_hash_table.entry,
                                                                              vm->current_frame->class_entry,
                                                                              entry->catch_type);
      if (caught) {
        operand_stack_push_u32(vm->current_frame, (uint32_t)objectref);
        vm->current_frame->next_pc = entry->handler_pc;

        debugs("vm_exception (handled)\n");
        debugs("current_frame:\n  class:  ");
        debug_print__class_file__class_name(vm->current_frame->class_entry->class_file);
        debugs("\n  method: ");
        debug_print__method_info__method_name(vm->current_frame->class_entry->class_file, vm->current_frame->method_info);
        debugf("\n  pc:      %d", vm->current_frame->pc);

        return;
      }
    }
    vm->current_frame = stack_pop_frame(&vm->frame_stack, 1);
  }

  prints("exception: ");
  print__class_file__class_name(exception_class_entry->class_file);
  printc('\n');
  {
    struct objectref * string_objectref = objectref->oref[1]; // message
    if (string_objectref != nullptr) {
      prints("  message: ");
      struct class_entry * string_class_entry = string_objectref->class_entry;
      prints("(class: ");
      print__class_file__class_name(string_class_entry->class_file);
      printc(')');
      prints("\n    ");
      struct arrayref * arrayref = string_objectref->aref[0];
      print_chars(arrayref->u16, arrayref->length);
      printc('\n');
    }
  }
  assert(objectref->oref[0] != 0);
  backtrace_print(objectref->oref[0]);
}

static void print_vm_stack(struct vm * vm)
{
  debugf("[  ");
  for (int i = 5; i > 0; i--) {
    if (i > vm->current_frame->operand_stack_ix) {
      debugf("            ");
      continue;
    }
    int32_t value = vm->current_frame->operand_stack[vm->current_frame->operand_stack_ix - i];
    if (value > 32767 || value < -32768)
      debugf("0x%08x  ", value);
    else
      debugf("%10d  ", value);
  }
  debugf("]\n");
}

void vm_execute(struct vm * vm)
{
  while (true) {
    assert(vm->current_frame->pc < vm->current_frame->code_attribute->code_length);
    print_vm_stack(vm);
#ifdef DEBUG_PRINT
    decode_print_instruction(vm->current_frame->code_attribute->code, vm->current_frame->pc);
#endif
    decode_execute_instruction(vm, vm->current_frame->code_attribute->code, vm->current_frame->pc);
    #ifdef MAIN_STRING_ARRAY
    if (vm->frame_stack.ix == 1) {
    #else
    if (vm->frame_stack.ix == 0) {
    #endif
      debugf("terminate\n");
      break;
    }
    vm->current_frame->pc = vm->current_frame->next_pc;
  }
}

struct vm * vm_start(int class_hash_table_length,
                     struct hash_table_entry * class_hash_table,
                     int native_hash_table_length,
                     struct hash_table_entry * native_hash_table,
                     const uint8_t * main_class_name,
                     int main_class_name_length)
{
  struct class_entry * class_entry = class_resolver_lookup_class(class_hash_table_length,
                                                                 class_hash_table,
                                                                 main_class_name,
                                                                 main_class_name_length);

  const uint8_t * method_name = (const uint8_t *)"main";
  int method_name_length = string_length((const char *)method_name);
  #ifdef MAIN_STRING_ARRAY
  const uint8_t * method_descriptor = (const uint8_t *)"([Ljava/lang/String;)V";
  #else
  const uint8_t * method_descriptor = (const uint8_t *)"()V";
  #endif
  int method_descriptor_length = string_length((const char *)method_descriptor);

  struct method_entry method_entry =
    class_resolver_lookup_method_from_method_name_method_descriptor(class_entry,
                                                                    method_name,
                                                                    method_name_length,
                                                                    method_descriptor,
                                                                    method_descriptor_length);
  assert(method_entry.method_info != nullptr);

  static struct vm vm;
  vm.class_hash_table.length = class_hash_table_length;
  vm.class_hash_table.entry = class_hash_table;
  vm.native_hash_table.length = native_hash_table_length;
  vm.native_hash_table.entry = native_hash_table;

  vm.frame_stack.ix = 0;
  vm.frame_stack.capacity = 1024;
  struct frame frames[vm.frame_stack.capacity];
  vm.frame_stack.frame = frames;

  vm.data_stack.ix = 0;
  vm.data_stack.capacity = 0x100000;
  uint32_t data[vm.data_stack.capacity];
  vm.data_stack.data = data;

  #ifdef MAIN_STRING_ARRAY
  {
    vm.current_frame = stack_push_frame(&vm.frame_stack, 1);
    vm.current_frame->operand_stack = stack_push_data(&vm.data_stack, 1);
    vm.current_frame->operand_stack_ix = 0;
    vm.current_frame->initialization_frame = 0;
    vm.current_frame->return_type = 0;

    // create empty arrayref

    struct arrayref * arrayref = ref_array_allocate(&vm, 0);
    assert(arrayref != nullptr);
    struct class_entry * string_class_entry = class_resolver_lookup_class(vm.class_hash_table.length,
                                                                          vm.class_hash_table.entry,
                                                                          (const uint8_t *)"java/lang/String",
                                                                          16);
    assert(class_entry != nullptr);
    arrayref->class_entry = string_class_entry;
    operand_stack_push_ref(vm.current_frame, arrayref);
  }
  #endif // MAIN_STRING_ARRAY

  vm_static_method_call(&vm, class_entry, &method_entry);

  return &vm;
}
