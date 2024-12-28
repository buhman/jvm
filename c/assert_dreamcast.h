#pragma once

#include "printf.h"
#include "class_file.h"

#define assert(b)                                                       \
  do {                                                                  \
    if (!(b)) {                                                         \
      printf("%s:%d %s: assertion `%s` failed\n", __FILE__, __LINE__, __func__, #b); \
      while (1);                                                        \
    }                                                                   \
  } while (0);

static inline void assert_print_string(struct constant * constant)
{
  for (int i = 0; i < constant->utf8.length; i++) {
    printc(constant->utf8.bytes[i]);
  }
  printc('\n');
}

#define assertvm(vm, b) \
do { \
  if (!(b)) { \
    printf("%s:%d %s: vm assertion `%s` failed\n", __FILE__, __LINE__, __func__, #b); \
 \
    struct class_entry * class_entry = vm->current_frame->class_entry; \
    struct constant * class_constant = &class_entry->class_file->constant_pool[class_entry->class_file->this_class - 1]; \
    assert(class_constant->tag == CONSTANT_Class); \
    struct constant * class_name_constant = &class_entry->class_file->constant_pool[class_constant->class.name_index - 1]; \
    assert(class_name_constant->tag == CONSTANT_Utf8); \
    assert_print_string(class_name_constant); \
 \
    struct method_info * method_info = vm->current_frame->method; \
    struct constant * method_name_constant = &class_entry->class_file->constant_pool[method_info->name_index - 1]; \
    assert(method_name_constant->tag == CONSTANT_Utf8); \
    assert_print_string(method_name_constant);               \
 \
    while (1); \
  } \
   } while (0);
