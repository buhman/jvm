#pragma once

#include <stdint.h>

struct hash_table_entry {
  const uint8_t * key;
  int key_length;
  void * value;
  struct hash_table_entry * next;
};

void hash_table_init(int hash_table_length,
                     struct hash_table_entry * entry);

void hash_table_add(int hash_table_length,
                    struct hash_table_entry * entry,
                    const uint8_t * key,
                    int key_length,
                    void * value);

struct hash_table_entry * hash_table_find(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key,
                                          int key_length);

void hash_table_add2(int hash_table_length,
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

void hash_table_add_int(int hash_table_length,
                        struct hash_table_entry * entry,
                        int key,
                        void * value);

struct hash_table_entry * hash_table_find_int(int hash_table_length,
                                              struct hash_table_entry * entry,
                                              int key);
