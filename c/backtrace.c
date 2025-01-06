#include "backtrace.h"
#include "printf.h"
#include "debug.h"
#include "find_attribute.h"
#include "memory_allocator.h"

struct backtrace * backtrace_allocate(struct vm * vm)
{
  struct backtrace * backtrace = memory_allocate((sizeof (struct backtrace)));
  backtrace->num_entries = vm->frame_stack.ix;
  int backtrace_entries_size = (sizeof (struct backtrace_entry)) * backtrace->num_entries;
  backtrace->entry = memory_allocate(backtrace_entries_size);

  for (int i = (vm->frame_stack.ix - 1); i >= 0; i--) {
    struct frame * frame = &vm->frame_stack.frame[i];
    backtrace->entry[i].class_file = frame->class_entry->class_file;
    backtrace->entry[i].method_info = frame->method_info;
    backtrace->entry[i].pc = frame->pc;
  }
  return backtrace;
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

void backtrace_print(struct backtrace * backtrace)
{
  prints("backtrace:\n");
  for (int i = (backtrace->num_entries - 1); i >= 0; i--) {
    struct backtrace_entry * backtrace_entry = &backtrace->entry[i];
    prints("  class: ");
    print__class_file__class_name(backtrace_entry->class_file);
    prints("  method: ");
    print__method_info__method_name(backtrace_entry->class_file, backtrace_entry->method_info);
    printc('\n');
    printf("    pc: %3d ", backtrace_entry->pc);
    int line_number = get_line_number(backtrace_entry->class_file,
                                      backtrace_entry->method_info,
                                      backtrace_entry->pc);
    printf("  line_number: %3d\n", line_number);
  }
}
