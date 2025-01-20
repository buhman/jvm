#pragma once

#include <stdint.h>

#include "class_file.h"
#include "hash_table.h"
#include "native_types.h"
#include "vm.h"

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

struct method_entry class_resolver_lookup_method_from_objectref_class(int class_hash_table_length,
                                                                      struct hash_table_entry * class_hash_table,
                                                                      int32_t methodref_index,
                                                                      struct class_entry * objectref_class_entry,
                                                                      struct class_entry * origin_class_entry);
struct method_entry * class_resolver_lookup_method_from_origin_class(int class_hash_table_length,
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

bool class_resolver_instanceof(int class_hash_table_length,
                               struct hash_table_entry * class_hash_table,
                               struct class_entry * origin_class_entry,
                               const int class_index,
                               struct objectref * objectref);

struct objectref * class_resolver_lookup_string(struct vm * vm,
                                                struct class_entry * class_entry,
                                                const int string_index);
