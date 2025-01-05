#include "backtrace.h"
#include "printf.h"
#include "debug.h"
#include "find_attribute.h"

void backtrace_print(struct vm * vm)
{
  for (int i = (vm->frame_stack.ix - 1); i >= 0; i--) {
    printf("ix %d\n", i);
    struct frame * frame = &vm->frame_stack.frame[i];
    printf("  class: ");
    print__class_entry__class_name(frame->class_entry);
    printc('\n');
    printf("  method: ");
    print__method_info__method_name(frame->class_entry, frame->method_info);
    printc('\n');
    printf("  pc: %d\n", frame->pc);

    int linenumbertable_name_index = find_linenumbertable_name_index(frame->class_entry->class_file);
    struct attribute_info * attribute_info = find_attribute(linenumbertable_name_index,
                                                            frame->code_attribute->attributes_count,
                                                            frame->code_attribute->attributes);
    assert(attribute_info != nullptr);
    int line_number_table_length = attribute_info->line_number_table->line_number_table_length;
    struct line_number_table * line_number_table = attribute_info->line_number_table->line_number_table;
    int line_number = 0;
    for (int i = 0; i < line_number_table_length; i++) {
      if (frame->pc >= line_number_table[i].start_pc) {
        line_number = line_number_table[i].line_number;
      } else {
        break;
      }
    }
    printf("  line_number: %d\n", line_number);
  }
}
