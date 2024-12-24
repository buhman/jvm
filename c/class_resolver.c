#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "class_file.h"
#include "file.h"
#include "hash_table.h"
#include "malloc.h"
#include "class_resolver.h"
#include "string.h"
#include "debug_class_file.h"

struct hash_table_entry * class_resolver_load_from_filenames(const char * filenames[], int length, int * hash_table_length)
{
  int class_hash_table_length = length * 2;
  uint32_t class_hash_table_size = (sizeof (struct hash_table_entry)) * class_hash_table_length;
  struct hash_table_entry * class_hash_table = malloc_class_arena(class_hash_table_size);
  uint32_t class_entry_size = (sizeof (struct class_entry)) * length;
  struct class_entry * class_entry = malloc_class_arena(class_entry_size);

  for (int i = 0; i < length; i++) {
    uint32_t filename_length = string_length(filenames[i]);
    const char * suffix = ".class";
    uint32_t suffix_length = string_length(suffix);
    const char * filename_suffix = &filenames[i][filename_length - suffix_length];
    if (filename_length <= suffix_length || !string_equal(suffix, filename_suffix)) {
      printf("invalid class filename: %s\n", filenames[i]);
      continue;
    }
    uint32_t class_name_length = filename_length - suffix_length;

    printf("load class: %s\n", filenames[i]);

    uint8_t * buf = file_read(filenames[i]);
    struct class_file * class_file = class_file_parse(buf);
    free(buf);

    assert(class_file->magic == 0xcafebabe);

    class_entry[i].class_file = class_file;

    hash_table_add(class_hash_table_length,
                   class_hash_table,
                   (const uint8_t *)filenames[i],
                   class_name_length,
                   &class_entry[i]);

    // make hash table for interfaces
    /*
    if (class_file->interfaces_count != 0) {
      uint32_t interfaces_hash_table_size = (sizeof (struct hash_table_entry)) * class_file->interfaces_count * 3 / 2;
      struct hash_table_entry * interfaces_hash_table = malloc_class_arena(interfaces_hash_table_size);
      for (int i = 0; i < class_file->interfaces_count; i++) {

      }
    }
    */
    // make hash table for fields
    if (class_file->fields_count != 0) {
      int fields_hash_table_length = class_file->fields_count * 2;
      uint32_t fields_hash_table_size = (sizeof (struct hash_table_entry)) * fields_hash_table_length;
      struct hash_table_entry * fields_hash_table = malloc_class_arena(fields_hash_table_size);
      uint32_t field_entry_size = (sizeof (struct field_entry)) * length;
      struct field_entry * field_entry = malloc_class_arena(field_entry_size);
      for (int i = 0; i < class_file->fields_count; i++) {
        u2 name_index = class_file->fields[i].name_index;
        struct constant * name_constant = &class_file->constant_pool[name_index - 1];
        assert(name_constant->tag == CONSTANT_Utf8);
        printf("hash table entry for field: ");
        print_utf8_string(name_constant);
        printf("\n");

        field_entry[i].field_info = &class_file->fields[i];
        field_entry[i].value = 0;

        hash_table_add(fields_hash_table_length,
                       fields_hash_table,
                       name_constant->utf8.bytes,
                       name_constant->utf8.length,
                       (void *)&field_entry[i]);
      }

      class_entry[i].fields.length = fields_hash_table_length;
      class_entry[i].fields.entry = fields_hash_table;
    }

    // make hash table for methods
    if (class_file->methods_count != 0) {
      int methods_hash_table_length = class_file->methods_count * 2;
      uint32_t methods_hash_table_size = (sizeof (struct hash_table_entry)) * methods_hash_table_length;
      struct hash_table_entry * methods_hash_table = malloc_class_arena(methods_hash_table_size);
      for (int i = 0; i < class_file->methods_count; i++) {
        u2 name_index = class_file->methods[i].name_index;
        struct constant * name_constant = &class_file->constant_pool[name_index - 1];
        assert(name_constant->tag == CONSTANT_Utf8);
        printf("hash table entry for method: ");
        print_utf8_string(name_constant);
        printf("\n");

        hash_table_add(methods_hash_table_length,
                       methods_hash_table,
                       name_constant->utf8.bytes,
                       name_constant->utf8.length,
                       (void *)&class_file->methods[i]);
      }

      class_entry[i].methods.length = methods_hash_table_length;
      class_entry[i].methods.entry = methods_hash_table;
    }
  };

  *hash_table_length = class_hash_table_length;

  return class_hash_table;
}

struct class_entry * class_resolver_lookup_class(int class_hash_table_length,
                                                 struct hash_table_entry * class_hash_table,
                                                 const uint8_t * class_name,
                                                 int class_name_length)
{
  printf("class_resolver_lookup_class: ");
  for (int i = 0; i < class_name_length; i++) { fputc(class_name[i], stdout); }
  fputc('\n', stdout);

  struct hash_table_entry * e = hash_table_find(class_hash_table_length,
                                                class_hash_table,
                                                class_name,
                                                class_name_length);
  assert(e != nullptr);

  return (struct class_entry *)e->value;
}


struct field_entry * class_resolver_lookup_field(struct class_entry * class_entry,
                                                 const uint8_t * field_name,
                                                 int field_name_length)
{
  printf("class_resolver_lookup_field: ");
  for (int i = 0; i < field_name_length; i++) { fputc(field_name[i], stdout); }
  fputc('\n', stdout);

  int fields_hash_table_length = class_entry->fields.length;
  struct hash_table_entry * fields_hash_table = class_entry->fields.entry;

  struct hash_table_entry * e = hash_table_find(fields_hash_table_length,
                                                fields_hash_table,
                                                field_name,
                                                field_name_length);
  assert(e != nullptr);

  return (struct field_entry *)e->value;
}

struct method_info * class_resolver_lookup_method(struct class_entry * class_entry,
                                                  const uint8_t * method_name,
                                                  int method_name_length)
{
  printf("class_resolver_lookup_method: ");
  for (int i = 0; i < method_name_length; i++) { fputc(method_name[i], stdout); }
  fputc('\n', stdout);

  int methods_hash_table_length = class_entry->methods.length;
  struct hash_table_entry * methods_hash_table = class_entry->methods.entry;

  struct hash_table_entry * e = hash_table_find(methods_hash_table_length,
                                                methods_hash_table,
                                                method_name,
                                                method_name_length);
  assert(e != nullptr);

  return (struct method_info *)e->value;
}
