#include "backtrace.h"
#include "printf.h"
#include "debug.h"
#include "find_attribute.h"
#include "memory_allocator.h"
#include "native_types_allocate.h"

struct objectref * backtrace_allocate(struct vm * vm)
{
  struct class_entry * class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                                                 vm->class_hash_table.entry,
                                                                 (const uint8_t *)"java/lang/Backtrace",
                                                                 19);
  debugf("backtrace class entry: %p\n", class_entry);

  assert(class_entry->instance_fields_count >= 1);
  struct objectref * objectref = obj_allocate(vm, class_entry->instance_fields_count);
  objectref->class_entry = class_entry;

  int num_entries = vm->frame_stack.ix;
  struct arrayref * arrayref = prim_array_allocate(vm, (sizeof (struct backtrace_entry)), num_entries);
  arrayref->length = num_entries;
  arrayref->class_entry = nullptr;

  struct backtrace_entry * backtrace_entry = (struct backtrace_entry *)&arrayref->u32[0];
  objectref->aref[0] = arrayref;

  for (int i = (num_entries - 1); i >= 0; i--) {
    struct frame * frame = &vm->frame_stack.frame[i];
    backtrace_entry[i].class_file = frame->class_entry->class_file;
    backtrace_entry[i].method_info = frame->method_info;
    backtrace_entry[i].pc = frame->pc;
  }
  return objectref;
}

static int get_line_number(struct class_file * class_file, struct method_info * method_info, int pc)
{
  int code_index = find_code_name_index(class_file);
  assert(code_index != 0);
  struct attribute_info * attribute = find_attribute(code_index,
                                                     method_info->attributes_count,
                                                     method_info->attributes);
  assert(attribute != nullptr);
  struct Code_attribute * code_attribute = attribute->code;

  int linenumbertable_name_index = find_linenumbertable_name_index(class_file);
  struct attribute_info * attribute_info = find_attribute(linenumbertable_name_index,
                                                          code_attribute->attributes_count,
                                                          code_attribute->attributes);
  assert(attribute_info != nullptr);
  int line_number_table_length = attribute_info->line_number_table->line_number_table_length;
  struct line_number_table * line_number_table = attribute_info->line_number_table->line_number_table;
  int line_number = 0;
  for (int i = 0; i < line_number_table_length; i++) {
    if (pc >= line_number_table[i].start_pc) {
      line_number = line_number_table[i].line_number;
    } else {
      break;
    }
  }
  return line_number;
}

void backtrace_print(struct objectref * objectref)
{
  debugf("backtrace objectref class entry: %p\n", objectref->class_entry);

  struct arrayref * arrayref = objectref->aref[0];
  struct backtrace_entry * backtrace_entry = (struct backtrace_entry *)&arrayref->u32[0];

  prints("backtrace:\n");
  for (int i = (arrayref->length - 1); i >= 0; i--) {
    struct backtrace_entry * entry = &backtrace_entry[i];
    prints("  class: ");
    print__class_file__class_name(entry->class_file);
    prints("  method: ");
    print__method_info__method_name(entry->class_file, entry->method_info);
    printc('\n');
    printf("    pc: %3d ", entry->pc);
    int line_number = get_line_number(entry->class_file,
                                      entry->method_info,
                                      entry->pc);
    printf("  line_number: %3d\n", line_number);
  }
}
