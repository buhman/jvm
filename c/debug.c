#include "printf.h"
#include "debug.h"
#include "assert.h"

void debug_print__string(const uint8_t * bytes, int length)
{
  for (int i = 0; i < length; i++) {
    debugc(bytes[i]);
  }
}

void debug_print__constant__utf8_string(struct constant * constant)
{
  assert(constant->tag == CONSTANT_Utf8);
  for (int i = 0; i < constant->utf8.length; i++) {
    debugc(constant->utf8.bytes[i]);
  }
}

void debug_print__class_entry__class_name(struct class_entry * class_entry)
{
  struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1];
  assert(class_constant->tag == CONSTANT_Class);
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  debug_print__constant__utf8_string(class_name_constant);
}

void debug_print__constant__method_name(struct constant * name_constant, struct constant * descriptor_constant)
{
  debug_print__constant__utf8_string(name_constant);
  debugc(' ');
  debug_print__constant__utf8_string(descriptor_constant);
}

void debug_print__method_info__method_name(struct class_entry * class_entry, struct method_info * method_info)
{
  struct constant * method_name_constant = &class_entry->class_file->constant_pool[method_info->name_index - 1];
  struct constant * method_descriptor_constant = &class_entry->class_file->constant_pool[method_info->descriptor_index - 1];
  debug_print__constant__method_name(method_name_constant, method_descriptor_constant);
}

void print__constant__utf8_string(struct constant * constant)
{
  assert(constant->tag == CONSTANT_Utf8);
  for (int i = 0; i < constant->utf8.length; i++) {
    printc(constant->utf8.bytes[i]);
  }
}

void print__class_entry__class_name(struct class_entry * class_entry)
{
  struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1];
  assert(class_constant->tag == CONSTANT_Class);
  struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1];
  print__constant__utf8_string(class_name_constant);
}

void print__constant__method_name(struct constant * name_constant, struct constant * descriptor_constant)
{
  print__constant__utf8_string(name_constant);
  printc(' ');
  print__constant__utf8_string(descriptor_constant);
}

void print__method_info__method_name(struct class_entry * class_entry, struct method_info * method_info)
{
  struct constant * method_name_constant = &class_entry->class_file->constant_pool[method_info->name_index - 1];
  struct constant * method_descriptor_constant = &class_entry->class_file->constant_pool[method_info->descriptor_index - 1];
  print__constant__method_name(method_name_constant, method_descriptor_constant);
}
