#pragma once

#include <stdint.h>

typedef uint64_t u8;
typedef uint32_t u4;
typedef uint16_t u2;
typedef uint8_t u1;

enum REF {
  REF_getField         = 1, //  getfield C.f:T
  REF_getStatic        = 2, //  getstatic C.f:T
  REF_putField         = 3, //  putfield C.f:T
  REF_putStatic        = 4, //  putstatic C.f:T
  REF_invokeVirtual    = 5, //  invokevirtual C.m:(A*)T
  REF_invokeStatic     = 6, //  invokestatic C.m:(A*)T
  REF_invokeSpecial    = 7, //  invokespecial C.m:(A*)T
  REF_newInvokeSpecial = 8, //  new C; dup; invokespecial C.<init>:(A*)V
  REF_invokeInterface  = 9, //  invokeinterface C.m:(A*)T
};

enum CONSTANT {
  CONSTANT_Class              = 7,  // §4.4.1
  CONSTANT_Fieldref           = 9,  // §4.4.2
  CONSTANT_Methodref          = 10, // §4.4.2
  CONSTANT_InterfaceMethodref = 11, // §4.4.2
  CONSTANT_String             = 8,  // §4.4.3
  CONSTANT_Integer            = 3,  // §4.4.4
  CONSTANT_Float              = 4,  // §4.4.4
  CONSTANT_Long               = 5,  // §4.4.5
  CONSTANT_Double             = 6,  // §4.4.5
  CONSTANT_NameAndType        = 12, // §4.4.6
  CONSTANT_Utf8               = 1,  // §4.4.7
  CONSTANT_MethodHandle       = 15, // §4.4.8
  CONSTANT_MethodType         = 16, // §4.4.9
  CONSTANT_Dynamic            = 17, // §4.4.10
  CONSTANT_InvokeDynamic      = 18, // §4.4.10
  CONSTANT_Module             = 19, // §4.4.11
  CONSTANT_Package            = 20, // §4.4.12
};

struct constant_Class_info {
  u2 name_index;
};

struct constant_Fieldref_info {
  u2 class_index;
  u2 name_and_type_index;
};

struct constant_Methodref_info {
  u2 class_index;
  u2 name_and_type_index;
};

struct constant_InterfaceMethodref_info {
  u2 class_index;
  u2 name_and_type_index;
};

struct constant_String_info {
  u2 string_index;
};

struct constant_Integer_info {
  u4 bytes;
};

struct constant_Float_info {
  u4 bytes;
};

struct constant_Long_info {
  u8 bytes;
};

struct constant_Double_info {
  u8 bytes;
};

struct constant_NameAndType_info {
  u2 name_index;
  u2 descriptor_index;
};

struct constant_Utf8_info {
  u2 length;
  u1 * bytes;
};

struct constant_MethodHandle_info {
  u1 reference_kind;
  u2 reference_index;
};

struct constant_MethodType_info {
  u2 descriptor_index;
};

struct constant_Dynamic_info {
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;
};

struct constant_InvokeDynamic_info {
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;
};

struct constant_Module_info {
  u2 name_index;
};

struct constant_Package_info {
  u2 name_index;
};

struct constant {
  #ifdef DEBUG
  u1 tag;
  #endif
  union {
    struct constant_Class_info class;
    struct constant_Fieldref_info fieldref;
    struct constant_Methodref_info methodref;
    struct constant_InterfaceMethodref_info interfacemethodref;
    struct constant_String_info string;
    struct constant_Integer_info integer;
    struct constant_Float_info _float;
    struct constant_Long_info _long;
    struct constant_Double_info _double;
    struct constant_NameAndType_info nameandtype;
    struct constant_Utf8_info utf8;
    struct constant_MethodHandle_info methodhandle;
    struct constant_MethodType_info methodtype;
    struct constant_Dynamic_info dynamic;
    struct constant_InvokeDynamic_info invokedynamic;
    struct constant_Module_info module;
    struct constant_Package_info package;
  };
};

struct ConstantValue_attribute;
struct Code_attribute;
struct StackMapTable_attribute;
struct BootstrapMethods_attribute;
struct NestHost_attribute;
struct NestMembers_attribute;
struct PermittedSubclasses_attribute;
struct LineNumberTable_attribute;
struct Exceptions_attribute;

struct attribute_info {
  u2 attribute_name_index;
  u4 attribute_length;
  union {
    void * info;
    struct ConstantValue_attribute * constantvalue;
    struct Code_attribute * code;
    //struct StackMapTable_attribute * stackmaptable;
    struct BootstrapMethods_attribute * bootstrap_methods;
    struct NestHost_attribute * nesthost;
    struct NestMembers_attribute * nestmembers;
    //struct PermittedSubclasses_attribute * permittedsubclasses;
    struct LineNumberTable_attribute * line_number_table;
    struct Exceptions_attribute * exceptions;
  };
};

struct ConstantValue_attribute {
  u2 constantvalue_index;
};

struct exception_table_entry {
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
};

struct Code_attribute {
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1 * code;
  u2 exception_table_length;
  struct exception_table_entry * exception_table;
  u2 attributes_count;
  struct attribute_info * attributes;
};

struct bootstrap_method {
  u2 bootstrap_method_ref;
  u2 num_bootstrap_arguments;
  u2 * bootstrap_arguments;
};

struct BootstrapMethods_attribute {
  u2 num_bootstrap_methods;
  struct bootstrap_method * bootstrap_methods;
};

struct NestHost_attribute {
  u2 host_class_index;
};

struct NestMembers_attribute {
  u2 number_of_classes;
  u2 * classes;
};

struct line_number_table {
  u2 start_pc;
  u2 line_number;
};

struct LineNumberTable_attribute {
  u2 line_number_table_length;
  struct line_number_table * line_number_table;
};

struct Exceptions_attribute {
  u2 number_of_exceptions;
  u2 * exception_index_table;
};

enum FIELD_ACC {
  FIELD_ACC_PUBLIC    = 0x0001, // Declared public; may be accessed from outside its package.
  FIELD_ACC_PRIVATE   = 0x0002, // Declared private; accessible only within the defining class and other classes belonging to the same nest (§5.4.4).
  FIELD_ACC_PROTECTED = 0x0004, // Declared protected; may be accessed within subclasses.
  FIELD_ACC_STATIC    = 0x0008, // Declared static.
  FIELD_ACC_FINAL     = 0x0010, // Declared final; never directly assigned to after object construction (JLS §17.5).
  FIELD_ACC_VOLATILE  = 0x0040, // Declared volatile; cannot be cached.
  FIELD_ACC_TRANSIENT = 0x0080, // Declared transient; not written or read by a persistent object manager.
  FIELD_ACC_SYNTHETIC = 0x1000, // Declared synthetic; not present in the source code.
  FIELD_ACC_ENUM      = 0x4000, // Declared as an element of an enum class.
};

struct field_info {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  struct attribute_info * attributes;
};

enum METHOD_ACC {
  METHOD_ACC_PUBLIC       = 0x0001, // Declared public; may be accessed from outside its package.
  METHOD_ACC_PRIVATE      = 0x0002, // Declared private; accessible only within the defining class and other classes belonging to the same nest (§5.4.4).
  METHOD_ACC_PROTECTED    = 0x0004, // Declared protected; may be accessed within subclasses.
  METHOD_ACC_STATIC       = 0x0008, // Declared static.
  METHOD_ACC_FINAL        = 0x0010, // Declared final; must not be overridden (§5.4.5).
  METHOD_ACC_SYNCHRONIZED = 0x0020, // Declared synchronized; invocation is wrapped by a monitor use.
  METHOD_ACC_BRIDGE       = 0x0040, // A bridge method, generated by the compiler.
  METHOD_ACC_VARARGS      = 0x0080, // Declared with variable number of arguments.
  METHOD_ACC_NATIVE       = 0x0100, // Declared native; implemented in a language other than the Java programming language.
  METHOD_ACC_ABSTRACT     = 0x0400, // Declared abstract; no implementation is provided.
  METHOD_ACC_STRICT       = 0x0800, // In a class file whose major version number is at least 46 and at most 60: Declared strictfp.
  METHOD_ACC_SYNTHETIC    = 0x1000, // Declared synthetic; not present in the source code.
};

struct method_info {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  struct attribute_info * attributes;
};

enum CLASS_ACC {
  CLASS_ACC_PUBLIC 	= 0x0001, // Declared public; may be accessed from outside its package.
  CLASS_ACC_FINAL 	= 0x0010, // Declared final; no subclasses allowed.
  CLASS_ACC_SUPER 	= 0x0020, // Treat superclass methods specially when invoked by the invokespecial instruction.
  CLASS_ACC_INTERFACE 	= 0x0200, // Is an interface, not a class.
  CLASS_ACC_ABSTRACT 	= 0x0400, // Declared abstract; must not be instantiated.
  CLASS_ACC_SYNTHETIC 	= 0x1000, // Declared synthetic; not present in the source code.
  CLASS_ACC_ANNOTATION 	= 0x2000, // Declared as an annotation interface.
  CLASS_ACC_ENUM 	= 0x4000, // Declared as an enum class.
  CLASS_ACC_MODULE      = 0x8000, // Is a module, not a class or interface.
};

struct class_file {
  u4 magic;
  u2 minor_version;
  u2 major_version;
  u2 constant_pool_count;
  struct constant * constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 * interfaces;
  u2 fields_count;
  struct field_info * fields;
  u2 methods_count;
  struct method_info * methods;
  u2 attributes_count;
  struct attribute_info * attributes;
};

struct class_file * class_file_parse(const uint8_t * buf);
