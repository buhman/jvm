#pragma once

#include <stdint.h>

#include "class_file.h"
#include "hash_table.h"

struct field_entry {
  struct field_info * field_info;
  uint32_t value;
};

struct class_entry {
  struct class_file * class_file;

  struct {
    int length;
    struct hash_table_entry * entry;
  } interfaces;

  struct {
    int length;
    struct hash_table_entry * entry;
  } fields;

  struct {
    int length;
    struct hash_table_entry * entry;
  } methods;
};

struct hash_table_entry * class_resolver_load_from_filenames(const char * filenames[], int length, int * hash_table_length);
struct class_entry * class_resolver_lookup_class(int class_hash_table_length,
                                                 struct hash_table_entry * class_hash_table,
                                                 const uint8_t * class_name,
                                                 int class_name_length);
struct method_info * class_resolver_lookup_method(struct class_entry * class_entry,
                                                  const uint8_t * method_name,
                                                  int method_name_length);
struct field_entry * class_resolver_lookup_field(struct class_entry * class_entry,
                                                 const uint8_t * field_name,
                                                 int field_name_length);
