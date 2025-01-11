// declared here due to circular frame.h include in class_resolver.h
struct objectref * class_resolver_lookup_string(struct vm * vm,
                                                struct class_entry * class_entry,
                                                const int string_index);

static inline struct field_entry * field_entry_from_constant_index(int class_hash_table_length,
                                                                   struct hash_table_entry * class_hash_table,
                                                                   struct class_entry * origin_class_entry,
                                                                   int32_t index,
                                                                   struct constant ** field_descriptor_constant)
{
  struct field_entry * field_entry = class_resolver_lookup_field_from_fieldref_index(class_hash_table_length,
                                                                                     class_hash_table,
                                                                                     origin_class_entry,
                                                                                     index);
  assert(field_entry != nullptr);

  struct constant * fieldref_constant = &origin_class_entry->class_file->constant_pool[index - 1];
  assert(fieldref_constant->tag == CONSTANT_Fieldref);
  struct constant * nameandtype_constant = &origin_class_entry->class_file->constant_pool[fieldref_constant->fieldref.name_and_type_index - 1];
  assert(nameandtype_constant->tag == CONSTANT_NameAndType);
  *field_descriptor_constant = &origin_class_entry->class_file->constant_pool[nameandtype_constant->nameandtype.descriptor_index - 1];
  assert((*field_descriptor_constant)->tag == CONSTANT_Utf8);

  return field_entry;
}
