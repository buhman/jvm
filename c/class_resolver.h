#pragma once

#include <stdint.h>

#include "class_file.h"
#include "hash_table.h"
#include "native_types.h"

enum initialization_state {
  CLASS_UNINITIALIZED,
  CLASS_INITIALIZING,
  CLASS_INITIALIZED,
};

struct method_entry {
  struct class_entry * class_entry;
  struct method_info * method_info;
  struct Code_attribute * code_attribute;
};

union attribute_entry {
  struct class_entry * class_entry;
  struct method_entry * method_entry;
  struct field_entry * field_entry;
  struct objectref * string_objectref;
};

struct field_entry {
  struct field_info * field_info;
  union {
    int32_t instance_index;
    int32_t static_index;
  };
};

struct class_entry {
  struct class_file * class_file;
  enum initialization_state initialization_state;
  union attribute_entry * attribute_entry;
  int32_t * static_fields;
  int32_t instance_fields_count;

  struct {
    int length;
    struct hash_table_entry * entry;
  } fields;

  struct {
    int length;
    struct hash_table_entry * entry;
  } methods;
};

struct hash_table_entry * class_resolver_load_from_buffers(const uint8_t ** buffers,
                                                           int length,
                                                           int * hash_table_length);
struct class_entry * class_resolver_lookup_class(int class_hash_table_length,
                                                 struct hash_table_entry * class_hash_table,
                                                 const uint8_t * class_name,
                                                 int class_name_length);
struct class_entry * class_resolver_lookup_class_from_class_index(int class_hash_table_length,
                                                                  struct hash_table_entry * class_hash_table,
                                                                  struct class_entry * class_entry,
                                                                  int32_t class_index);
struct method_entry class_resolver_lookup_method_from_interfacemethodref_index(int class_hash_table_length,
                                                                               struct hash_table_entry * class_hash_table,
                                                                               int32_t interfacemethodref_index,
                                                                               struct class_entry * objectref_class_entry,
                                                                               struct class_entry * origin_class_entry);
struct method_entry * class_resolver_lookup_method_from_methodref_index(int class_hash_table_length,
                                                                        struct hash_table_entry * class_hash_table,
                                                                        int32_t methodref_index,
                                                                        struct class_entry * origin_class_entry);
struct method_entry class_resolver_lookup_method_from_method_name_method_descriptor(struct class_entry * class_entry,
                                                                                    const uint8_t * method_name,
                                                                                    int method_name_length,
                                                                                    const uint8_t * method_descriptor,
                                                                                    int method_descriptor_length);
struct field_entry * class_resolver_lookup_field(int fields_hash_table_length,
                                                 struct hash_table_entry * fields_hash_table,
                                                 const uint8_t * field_name,
                                                 int index);
struct field_entry * class_resolver_lookup_field_from_fieldref_index(int fields_hash_table_length,
                                                                     struct hash_table_entry * fields_hash_table,
                                                                     struct class_entry * class_entry,
                                                                     int fieldref_index);

struct objectref * class_resolver_lookup_string(int class_hash_table_length,
                                                struct hash_table_entry * class_hash_table,
                                                struct class_entry * class_entry,
                                                const int string_index);

bool class_resolver_instanceof(int class_hash_table_length,
                               struct hash_table_entry * class_hash_table,
                               struct class_entry * origin_class_entry,
                               const int class_index,
                               struct objectref * objectref);
