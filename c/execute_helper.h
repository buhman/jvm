#include "debug_class_file.h"

static inline void class_entry_field_entry_from_constant_index(struct vm * vm,
                                                               int32_t index,
                                                               struct class_entry ** class_entry,
                                                               struct field_entry ** field_entry,
                                                               struct constant ** field_descriptor_constant)
{
  struct constant * fieldref_constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  #ifdef DEBUG
  assert(fieldref_constant->tag == CONSTANT_Fieldref);
  #endif

  *class_entry = class_resolver_lookup_class_from_class_index(vm->class_hash_table.length,
                                                              vm->class_hash_table.entry,
                                                              vm->current_frame->class_entry,
                                                              fieldref_constant->fieldref.class_index);

  assert(*class_entry != nullptr);

  int fields_hash_table_length = (*class_entry)->fields.length;
  struct hash_table_entry * fields_hash_table = (*class_entry)->fields.entry;

  *field_entry = class_resolver_lookup_field_from_fieldref_index(fields_hash_table_length,
                                                                 fields_hash_table,
                                                                 vm->current_frame->class_entry,
                                                                 index);
  assert(*field_entry != nullptr);

  struct constant * nameandtype_constant = &vm->current_frame->class_entry->class_file->constant_pool[fieldref_constant->fieldref.name_and_type_index - 1];
  #ifdef DEBUG
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  #endif
  *field_descriptor_constant = &vm->current_frame->class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  #ifdef DEBUG
  assert((*field_descriptor_constant)->tag == CONSTANT_Utf8);
  #endif
}

static inline void class_entry_method_info_from_constant_index(struct vm * vm,
                                                               int32_t index,
                                                               struct class_entry ** class_entry,
                                                               struct method_info ** method_info)
{
  struct constant * methodref_constant = &vm->current_frame->class_entry->class_file->constant_pool[index - 1];
  #ifdef DEBUG
  assert(methodref_constant->tag == CONSTANT_Methodref);
  #endif

  *class_entry = class_resolver_lookup_class_from_class_index(vm->class_hash_table.length,
                                                              vm->class_hash_table.entry,
                                                              vm->current_frame->class_entry,
                                                              methodref_constant->methodref.class_index);
  assert(*class_entry != nullptr);

  int methods_hash_table_length = (*class_entry)->methods.length;
  struct hash_table_entry * methods_hash_table = (*class_entry)->methods.entry;

  *method_info = class_resolver_lookup_method_from_methodref_index(methods_hash_table_length,
                                                                   methods_hash_table,
                                                                   vm->current_frame->class_entry,
                                                                   index);
  assert(*method_info != nullptr);
}
