#include "assert.h"
#include "class_file.h"
#include "bytes.h"
#include "debug.h"
#include "printf.h"

int find_code_name_index(struct class_file * class_file)
{
  for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    if (constant->tag == CONSTANT_Utf8) {
      if (constant_equal(constant, "Code")) {
        return i + 1;
      }
    }
  }
  return 0;
}

int find_constantvalue_name_index(struct class_file * class_file)
{
  for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    if (constant->tag == CONSTANT_Utf8) {
      if (constant_equal(constant, "ConstantValue")) {
        return i + 1;
      }
    }
  }
  return 0;
}

int find_linenumbertable_name_index(struct class_file * class_file)
{
  for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    if (constant->tag == CONSTANT_Utf8) {
      if (constant_equal(constant, "LineNumberTable")) {
        return i + 1;
      }
    }
  }
  return 0;
}

struct attribute_info * find_attribute(int name_index,
                                       int attributes_count,
                                       struct attribute_info * attributes)
{
  //debugf("find_attribute: name_index=%d attributes_count=%d\n", name_index, attributes_count);
  for (int i = 0; i < attributes_count; i++) {
    //debugf("find_attribute: attribute[%d]: %d\n", i, attributes[i].attribute_name_index);
    if (attributes[i].attribute_name_index == name_index)
      return &attributes[i];
  }
  return nullptr;
}
