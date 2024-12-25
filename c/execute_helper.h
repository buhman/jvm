#include "debug_class_file.h"

static inline void class_entry_field_entry_from_constant_index(struct vm * vm,
                                                               uint32_t index,
                                                               struct class_entry ** class_entry,
                                                               struct field_entry ** field_entry,
                                                               struct constant ** field_descriptor_constant)
{
  struct constant * fieldref_constant = &vm->current_frame->class->constant_pool[index - 1];
  #ifdef DEBUG
  assert(fieldref_constant->tag == CONSTANT_Fieldref);
  #endif
  struct constant * class_constant = &vm->current_frame->class->constant_pool[fieldref_constant->fieldref.class_index - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * nameandtype_constant = &vm->current_frame->class->constant_pool[fieldref_constant->fieldref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  struct constant * class_name_constant = &vm->current_frame->class->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif
  struct constant * field_name_constant = &vm->current_frame->class->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  #ifdef DEBUG
  assert(field_name_constant->tag == CONSTANT_Utf8);
  #endif
  *field_descriptor_constant = &vm->current_frame->class->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  #ifdef DEBUG
  assert((*field_descriptor_constant)->tag == CONSTANT_Utf8);
  #endif

  *class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                             vm->class_hash_table.entry,
                                             class_name_constant->utf8.bytes,
                                             class_name_constant->utf8.length);
  assert(*class_entry != nullptr);

  *field_entry = class_resolver_lookup_field(*class_entry,
                                             field_name_constant->utf8.bytes,
                                             field_name_constant->utf8.length);
  assert(*field_entry != nullptr);
}

static inline void class_entry_method_info_from_constant_index(struct vm * vm,
                                                               uint32_t index,
                                                               struct class_entry ** class_entry,
                                                               struct method_info ** method_info)
{
  struct constant * methodref_constant = &vm->current_frame->class->constant_pool[index - 1];
  #ifdef DEBUG
  assert(methodref_constant->tag == CONSTANT_Methodref);
  #endif
  struct constant * class_constant = &vm->current_frame->class->constant_pool[methodref_constant->methodref.class_index - 1];
  #ifdef DEBUG
  assert(class_constant->tag == CONSTANT_Class);
  #endif
  struct constant * nameandtype_constant = &vm->current_frame->class->constant_pool[methodref_constant->methodref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  struct constant * class_name_constant = &vm->current_frame->class->constant_pool[class_constant->class.name_index - 1];
  #ifdef DEBUG
  assert(class_name_constant->tag == CONSTANT_Utf8);
  #endif
  struct constant * method_name_constant = &vm->current_frame->class->constant_pool[nameandtype_constant->nameandtype.name_index - 1];
  #ifdef DEBUG
  assert(method_name_constant->tag == CONSTANT_Utf8);
  #endif
  struct constant * method_descriptor_constant = &vm->current_frame->class->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  #ifdef DEBUG
  assert(method_descriptor_constant->tag == CONSTANT_Utf8);
  #endif

  *class_entry = class_resolver_lookup_class(vm->class_hash_table.length,
                                             vm->class_hash_table.entry,
                                             class_name_constant->utf8.bytes,
                                             class_name_constant->utf8.length);
  assert(*class_entry != nullptr);

  *method_info = class_resolver_lookup_method(*class_entry,
                                              method_name_constant->utf8.bytes,
                                              method_name_constant->utf8.length,
                                              method_descriptor_constant->utf8.bytes,
                                              method_descriptor_constant->utf8.length);
  assert(*method_info != nullptr);
}
