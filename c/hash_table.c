#include "assert.h"
#include "malloc.h"
#include "hash_table.h"
#include "printf.h"

static const uint32_t fnv_offset_basis = 0x811c9dc5;

int32_t hash_table_next_power_of_two(int32_t n)
{
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;
  return n;
}

static uint32_t fnv_1(uint32_t hash, const uint8_t * buf, int length)
{
  const uint32_t fnv_prime = 0x01000193;

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

void print_key(const uint8_t * key, int key_length)
{
  debugf("key: ");
  for (int i = 0; i < key_length; i++)
    debugc(key[i]);
  debugc('\n');
}

struct hash_table_entry * hash_table_add(int hash_table_length,
                                         struct hash_table_entry * entry,
                                         const uint8_t * key,
                                         int key_length,
                                         void * value)
{
  assert(hash_table_length != 0);
  assert((hash_table_length & (hash_table_length - 1)) == 0);
  uint32_t hash = fnv_1(fnv_offset_basis, key, key_length) & (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e->next != nullptr) {
    e = e->next;
  }

  if (e->key != nullptr) {
    // allocate e from overflow
    e->next = malloc_class_arena((sizeof (struct hash_table_entry)));
    e->next->key = nullptr;
    e->next->next = nullptr;
    e = e->next;
  }

  uint8_t * key_copy = malloc_class_arena(key_length);
  for (int i = 0; i < key_length; i++) key_copy[i] = key[i];
  e->key = key_copy;
  e->key_length = key_length;
  e->value = value;

  return e;
}

struct hash_table_entry * hash_table_find(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key,
                                          int key_length)
{
  if (hash_table_length == 0)
    return nullptr;

  assert((hash_table_length & (hash_table_length - 1)) == 0);
  uint32_t hash = fnv_1(fnv_offset_basis, key, key_length) & (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e != nullptr && e->key != nullptr) {
    //debugf("key find: %p ", e->key);
    //print_key(e->key, e->key_length);
    if (e->key_length == key_length && hash_table_key_equal(key, e->key, e->key_length)) {
      return e;
    }
    e = e->next;
  }
  return nullptr;
}

static inline bool key_equal2(const uint8_t * a1, int a1_length,
                              const uint8_t * a2, int a2_length,
                              const uint8_t * b)
{
  for (int i = 0; i < a1_length; i++) {
    if (a1[i] != b[i])
      return false;
  }
  for (int i = 0; i < a2_length; i++) {
    if (a2[i] != b[a1_length + i])
      return false;
  }
  return true;
}

struct hash_table_entry * hash_table_add2(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key1,
                                          int key1_length,
                                          const uint8_t * key2,
                                          int key2_length,
                                          void * value)
{
  assert(hash_table_length != 0);
  assert((hash_table_length & (hash_table_length - 1)) == 0);
  uint32_t hash = fnv_offset_basis;
  hash = fnv_1(hash, key1, key1_length);
  hash = fnv_1(hash, key2, key2_length);
  hash &= (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e->next != nullptr) {
    e = e->next;
  }

  if (e->key != nullptr) {
    // allocate e from overflow
    e->next = malloc_class_arena((sizeof (struct hash_table_entry)));
    e->next->key = nullptr;
    e->next->next = nullptr;
    e = e->next;
  }

  uint8_t * key_copy = malloc_class_arena(key1_length + key2_length);
  for (int i = 0; i < key1_length; i++) key_copy[i] = key1[i];
  for (int i = 0; i < key2_length; i++) key_copy[key1_length + i] = key2[i];
  e->key = key_copy;
  e->key_length = key1_length + key2_length;
  e->value = value;

  return e;
}

struct hash_table_entry * hash_table_find2(int hash_table_length,
                                           struct hash_table_entry * entry,
                                           const uint8_t * key1,
                                           int key1_length,
                                           const uint8_t * key2,
                                           int key2_length)
{
  if (hash_table_length == 0)
    return nullptr;

  assert((hash_table_length & (hash_table_length - 1)) == 0);
  uint32_t hash = fnv_offset_basis;
  hash = fnv_1(hash, key1, key1_length);
  hash = fnv_1(hash, key2, key2_length);
  hash &= (hash_table_length - 1);

  struct hash_table_entry * e = &entry[hash];

  while (e != nullptr && e->key != nullptr) {
    bool equal =
      e->key_length == (key1_length + key2_length) &&
      key_equal2(key1, key1_length,
                 key2, key2_length,
                 e->key);
    if (equal) {
      return e;
    }
    e = e->next;
  }
  return nullptr;
}

struct hash_table_entry * hash_table_add3(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          const uint8_t * key1,
                                          int key1_length,
                                          const uint8_t * key2,
                                          int key2_length,
                                          const uint8_t * key3,
                                          int key3_length,
                                          void * value)
{
  assert(hash_table_length != 0);
  assert((hash_table_length & (hash_table_length - 1)) == 0);
  uint32_t hash = fnv_offset_basis;
  hash = fnv_1(hash, key1, key1_length);
  hash = fnv_1(hash, key2, key2_length);
  hash = fnv_1(hash, key3, key3_length);
  hash &= (hash_table_length - 1);

  struct hash_table_entry * e = &entry[hash];

  while (e->next != nullptr) {
    e = e->next;
  }

  if (e->key != nullptr) {
    // allocate e from overflow
    e->next = malloc_class_arena((sizeof (struct hash_table_entry)));
    e->next->key = nullptr;
    e->next->next = nullptr;
    e = e->next;
  }

  uint8_t * key_copy = malloc_class_arena(key1_length + key2_length + key3_length);
  for (int i = 0; i < key1_length; i++) key_copy[i] = key1[i];
  for (int i = 0; i < key2_length; i++) key_copy[key1_length + i] = key2[i];
  for (int i = 0; i < key3_length; i++) key_copy[key1_length + key2_length + i] = key3[i];
  e->key = key_copy;
  e->key_length = key1_length + key2_length + key3_length;
  e->value = value;

  return e;
}

static inline bool key_equal3(const uint8_t * a1, int a1_length,
                              const uint8_t * a2, int a2_length,
                              const uint8_t * a3, int a3_length,
                              const uint8_t * b)
{
  for (int i = 0; i < a1_length; i++) {
    if (a1[i] != b[i])
      return false;
  }
  for (int i = 0; i < a2_length; i++) {
    if (a2[i] != b[a1_length + i])
      return false;
  }
  for (int i = 0; i < a3_length; i++) {
    if (a3[i] != b[a1_length + a2_length + i])
      return false;
  }
  return true;
}

struct hash_table_entry * hash_table_find3(int hash_table_length,
                                           struct hash_table_entry * entry,
                                           const uint8_t * key1,
                                           int key1_length,
                                           const uint8_t * key2,
                                           int key2_length,
                                           const uint8_t * key3,
                                           int key3_length)
{
  if (hash_table_length == 0)
    return nullptr;

  assert((hash_table_length & (hash_table_length - 1)) == 0);
  uint32_t hash = fnv_offset_basis;
  hash = fnv_1(hash, key1, key1_length);
  hash = fnv_1(hash, key2, key2_length);
  hash = fnv_1(hash, key3, key3_length);
  hash &= (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e != nullptr && e->key != nullptr) {
    bool equal =
      e->key_length == (key1_length + key2_length + key3_length) &&
      key_equal3(key1, key1_length,
                 key2, key2_length,
                 key3, key3_length,
                 e->key);
    if (equal) {
      return e;
    }
    e = e->next;
  }
  return nullptr;
}
