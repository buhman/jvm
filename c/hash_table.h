#pragma once

#include <stdint.h>

struct hash_table_entry {
  const uint8_t * key;
  int key_length;
  void * value;
  struct hash_table_entry * next;
};

int32_t hash_table_next_power_of_two(int32_t n);

void hash_table_init(int hash_table_length,
                     struct hash_table_entry * entry);

struct hash_table_entry * hash_table_add(int hash_table_length,
                                         struct hash_table_entry * entry,
                                         const uint8_t * key,
                                         int key_length,
                                         void * value);

struct hash_table_entry * hash_table_find(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key,
                                          int key_length);

struct hash_table_entry * hash_table_add2(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key1,
                                          int key1_length,
                                          const uint8_t * key2,
                                          int key2_length,
                                          void * value);

struct hash_table_entry * hash_table_find2(int hash_table_length,
                                           struct hash_table_entry * entry,
                                           const uint8_t * key1,
                                           int key1_length,
                                           const uint8_t * key2,
                                           int key2_length);

struct hash_table_entry * hash_table_add3(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key1,
                                          int key1_length,
                                          const uint8_t * key2,
                                          int key2_length,
                                          const uint8_t * key3,
                                          int key3_length,
                                          void * value);

struct hash_table_entry * hash_table_find3(int hash_table_length,
                                           struct hash_table_entry * entry,
                                           const uint8_t * key1,
                                           int key1_length,
                                           const uint8_t * key2,
                                           int key2_length,
                                           const uint8_t * key3,
                                           int key3_length);

static inline bool hash_table_key_equal(const uint8_t * a, const uint8_t * b, int length)
{
  for (int i = 0; i < length; i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}
