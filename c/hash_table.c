#include "malloc.h"
#include "hash_table.h"

static uint32_t fnv_1(const uint8_t * buf, int length)
{
  const uint32_t fnv_offset_basis = 0x811c9dc5;
  const uint32_t fnv_prime = 0x01000193;

  uint32_t hash = fnv_offset_basis;

  for (int i = 0; i < length; i++) {
    hash = hash * fnv_prime;
    hash = hash ^ buf[i];
  }

  return hash;
}

void hash_table_init(int hash_table_length,
                     struct hash_table_entry * entry)
{
  for (int i = 0; i < hash_table_length; i++) {
    entry[i].key = nullptr;
    entry[i].next = nullptr;
  }
}

void hash_table_add(int hash_table_length,
                    struct hash_table_entry * entry,
                    const uint8_t * key,
                    int key_length,
                    void * value)
{
  uint32_t hash = fnv_1(key, key_length) & (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e->next != nullptr) {
    e = e->next;
  }

  if (e->key != nullptr) {
    // allocate e from overflow
    e->next = malloc_class_arena((sizeof (struct hash_table_entry)));
    e = e->next;
  }

  e->key = key;
  e->key_length = key_length;
  e->value = value;
}

static inline bool key_equal(const uint8_t * a, const uint8_t * b, int length)
{
  for (int i = 0; i < length; i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

struct hash_table_entry * hash_table_find(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key,
                                          int key_length)
{
  uint32_t hash = fnv_1(key, key_length) & (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e != nullptr && e->key != nullptr) {
    if (e->key_length == key_length && key_equal(e->key, key, key_length)) {
      return e;
    }
    e = e->next;
  }
  return nullptr;
}
