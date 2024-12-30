#include "printf.h"
#include "debug.h"
#include "assert.h"

void debug_print__constant__utf8_string(struct constant * constant)
{
  for (int i = 0; i < constant->utf8.length; i++) {
    debugc(constant->utf8.bytes[i]);
  }
}

void debug_print__class_entry__class_name(struct class_entry * class_entry)
{
  struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1];
  assert(class_constant->tag == CONSTANT_Class);
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  assert(class_name_constant->tag == CONSTANT_Utf8);
  debug_print__constant__utf8_string(class_name_constant);
}

void debug_print__method_info__method_name(struct class_entry * class_entry, struct method_info * method_info)
{
  struct constant * method_name_constant = &class_entry->class_file->constant_pool[method_info->name_index - 1];
  assert(method_name_constant->tag == CONSTANT_Utf8);
  debug_print__constant__utf8_string(method_name_constant);

  debugc(' ');

  struct constant * method_descriptor_constant = &class_entry->class_file->constant_pool[method_info->descriptor_index - 1];
  assert(method_descriptor_constant->tag == CONSTANT_Utf8);
  debug_print__constant__utf8_string(method_descriptor_constant);
}

void debug_print__constant__method_name(struct constant * name_constant, struct constant * descriptor_constant)
{
  assert(name_constant->tag == CONSTANT_Utf8);
  debug_print__constant__utf8_string(name_constant);
  debugc(' ');
  assert(descriptor_constant->tag == CONSTANT_Utf8);
  debug_print__constant__utf8_string(descriptor_constant);
}
