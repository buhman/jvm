#include "hash_table.h"
#include "malloc.h"
#include "string.h"
#include "printf.h"
#include "native.h"
#include "native/class.h"
#include "native/libcinputstream.h"
#include "native/loader.h"
#include "native/math.h"
#include "native/memory.h"
#include "native/object.h"
#include "native/printstream.h"
#include "native/runtime.h"
#include "native/system.h"

typedef void (* native_func_t)(struct vm * vm, uint32_t * args);

struct native_method {
  const char * class_name;
  const char * method_name;
  const char * method_descriptor;
  native_func_t func;
};

const static struct native_method native_method[] = {
  // Math
  {
    .class_name = "java/lang/Math",
    .method_name = "sin",
    .method_descriptor = "(F)F",
    .func = native_java_lang_math_sin_1,
  },
  {
    .class_name = "java/lang/Math",
    .method_name = "cos",
    .method_descriptor = "(F)F",
    .func = native_java_lang_math_cos_1,
  },
  {
    .class_name = "java/lang/Math",
    .method_name = "abs",
    .method_descriptor = "(F)F",
    .func = native_java_lang_math_abs_1,
  },
  // Memory
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "putU4",
    .method_descriptor = "(II)V",
    .func = native_jvm_internal_memory_putU4_2,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "putU2",
    .method_descriptor = "(IS)V",
    .func = native_jvm_internal_memory_putU2_2,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "putU1",
    .method_descriptor = "(IB)V",
    .func = native_jvm_internal_memory_putU1_2,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "getU4",
    .method_descriptor = "(I)I",
    .func = native_jvm_internal_memory_getU4_1,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "getU2",
    .method_descriptor = "(I)S",
    .func = native_jvm_internal_memory_getU2_1,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "getU1",
    .method_descriptor = "(I)B",
    .func = native_jvm_internal_memory_getU1_1,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "putU4",
    .method_descriptor = "(IIZ)V",
    .func = native_jvm_internal_memory_putUnalignedU4_3,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "putU2",
    .method_descriptor = "(ISZ)V",
    .func = native_jvm_internal_memory_putUnalignedU2_3,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "putF4",
    .method_descriptor = "(IFZ)V",
    .func = native_jvm_internal_memory_putUnalignedU4_3,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "getU4",
    .method_descriptor = "(IZ)I",
    .func = native_jvm_internal_memory_getUnalignedU4_2,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "getU2",
    .method_descriptor = "(IZ)S",
    .func = native_jvm_internal_memory_getUnalignedU2_2,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "getF4",
    .method_descriptor = "(IZ)F",
    .func = native_jvm_internal_memory_getUnalignedU4_2,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "isBigEndian",
    .method_descriptor = "()Z",
    .func = native_jvm_internal_memory_isbigendian_0,
  },
  {
    .class_name = "jvm/internal/Memory",
    .method_name = "allocate",
    .method_descriptor = "(I)I",
    .func = native_jvm_internal_memory_allocate_1,
  },
  // PrintStream
  {
    .class_name = "java/io/PrintStream",
    .method_name = "_write",
    .method_descriptor = "([B)V",
    .func = native_java_io_printstream_write_ba_1,
  },
  {
    .class_name = "java/io/PrintStream",
    .method_name = "_write",
    .method_descriptor = "([C)V",
    .func = native_java_io_printstream_write_ca_1,
  },
  {
    .class_name = "java/io/PrintStream",
    .method_name = "_write",
    .method_descriptor = "(Ljava/lang/String;)V",
    .func = native_java_io_printstream_write_s_1,
  },
  // Loader
  {
    .class_name = "jvm/internal/Loader",
    .method_name = "load",
    .method_descriptor = "([II)V",
    .func = native_jvm_internal_loader_load_2,
  },
  {
    .class_name = "jvm/internal/Loader",
    .method_name = "getBuffer",
    .method_descriptor = "()I",
    .func = native_jvm_internal_loader_getbuffer_0,
  },
  // Class
  {
    .class_name = "java/lang/Class",
    .method_name = "_getName",
    .method_descriptor = "(Ljava/lang/Object;)Ljava/lang/String;",
    .func = native_java_lang_class_getname_1,
  },
  {
    .class_name = "java/lang/Class",
    .method_name = "_getSuperclass",
    .method_descriptor = "(Ljava/lang/Object;)Ljava/lang/String;",
    .func = native_java_lang_class_getsuperclass_1,
  },
  // Object
  {
    .class_name = "java/lang/Object",
    .method_name = "_getClass",
    .method_descriptor = "(Ljava/lang/Object;)Ljava/lang/Class;",
    .func = native_java_lang_object_getclass_1,
  },
  // Runtime
  {
    .class_name = "java/lang/Runtime",
    .method_name = "_freeMemory",
    .method_descriptor = "()I",
    .func = native_java_lang_runtime_freememory_0,
  },
  {
    .class_name = "java/lang/Runtime",
    .method_name = "_gc",
    .method_descriptor = "()V",
    .func = native_java_lang_runtime_gc_0,
  },
  {
    .class_name = "java/lang/Runtime",
    .method_name = "_totalMemory",
    .method_descriptor = "()I",
    .func = native_java_lang_runtime_totalmemory_0,
  },
  // System
  {
    .class_name = "java/lang/System",
    .method_name = "_hashCode",
    .method_descriptor = "(Ljava/lang/Object;)I",
    .func = native_java_lang_system_hashcode_1,
  },
#if !defined(__dreamcast__)
  {
    .class_name = "jvm/internal/LibcInputStream",
    .method_name = "_open",
    .method_descriptor = "([B)I",
    .func = native_jvm_internal_libcinputstream_open_1,
  },
  {
    .class_name = "jvm/internal/LibcInputStream",
    .method_name = "_available",
    .method_descriptor = "(I)I",
    .func = native_jvm_internal_libcinputstream_available_1,
  },
  {
    .class_name = "jvm/internal/LibcInputStream",
    .method_name = "_close",
    .method_descriptor = "(I)V",
    .func = native_jvm_internal_libcinputstream_close_1,
  },
  {
    .class_name = "jvm/internal/LibcInputStream",
    .method_name = "_read",
    .method_descriptor = "(I)I",
    .func = native_jvm_internal_libcinputstream_read_1,
  },
#endif
};

struct hash_table_entry * native_init_hash_table(int * hash_table_length)
{
  int native_length = (sizeof (native_method)) / (sizeof (native_method[0]));
  int native_hash_table_length = hash_table_next_power_of_two(native_length * 2);
  uint32_t native_hash_table_size = (sizeof (struct hash_table_entry)) * native_hash_table_length;
  struct hash_table_entry * native_hash_table = malloc_class_arena(native_hash_table_size);
  hash_table_init(native_hash_table_length, native_hash_table);

  for (int i = 0; i < native_length; i++) {
    assert(native_method[i].class_name != nullptr);
    assert(native_method[i].method_name != nullptr);
    assert(native_method[i].method_descriptor != nullptr);
    assert(native_method[i].func != nullptr);

    int class_name_length = string_length(native_method[i].class_name);
    int method_name_length = string_length(native_method[i].method_name);
    int method_descriptor_length = string_length(native_method[i].method_descriptor);

    debugf("native_init_hash_table add:  %s  %s  %s  →  %p\n",
           native_method[i].class_name,
           native_method[i].method_name,
           native_method[i].method_descriptor,
           native_method[i].func
           );

    hash_table_add3(native_hash_table_length,
                    native_hash_table,
                    (const uint8_t *)native_method[i].class_name,
                    class_name_length,
                    (const uint8_t *)native_method[i].method_name,
                    method_name_length,
                    (const uint8_t *)native_method[i].method_descriptor,
                    method_descriptor_length,
                    native_method[i].func
                    );
  }

  *hash_table_length = native_hash_table_length;
  return native_hash_table;
}

void native_method_call(struct vm * vm,
                        struct constant * class_name_constant,
                        struct constant * method_name_constant,
                        struct constant * method_descriptor_constant,
                        uint32_t * args)
{
  struct hash_table_entry * e = hash_table_find3(vm->native_hash_table.length,
                                                 vm->native_hash_table.entry,
                                                 class_name_constant->utf8.bytes,
                                                 class_name_constant->utf8.length,
                                                 method_name_constant->utf8.bytes,
                                                 method_name_constant->utf8.length,
                                                 method_descriptor_constant->utf8.bytes,
                                                 method_descriptor_constant->utf8.length
                                                 );
  if (e == nullptr) {
    print_bytes(class_name_constant->utf8.bytes, class_name_constant->utf8.length);
    printc(' ');
    print_bytes(method_name_constant->utf8.bytes, method_name_constant->utf8.length);
    printc(' ');
    print_bytes(method_descriptor_constant->utf8.bytes, method_descriptor_constant->utf8.length);
    printc('\n');
  }
  assert(e != nullptr);
  assert(e->value != nullptr);

  native_func_t func = (native_func_t)e->value;
  func(vm, args);
}
