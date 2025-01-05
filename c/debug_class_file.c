#include <stdint.h>

#include "assert.h"
#include "class_file.h"
#include "bytes.h"
#include "decode.h"
#include "debug_class_file.h"
#include "printf.h"
#include "string.h"
#include "debug.h"

static void print_attribute(const char * indent, struct attribute_info * attribute, struct constant * constant_pool);

static void print_constant(struct constant * constant)
{
  switch (constant->tag) {
  case CONSTANT_Class:
    printf("CONSTANT_Class name_index=%d\n",
           constant->class.name_index);
    break;
  case CONSTANT_Fieldref:
    printf("CONSTANT_Fieldref class_index=%d name_and_type_index=%d\n",
           constant->fieldref.class_index,
           constant->fieldref.name_and_type_index);
    break;
  case CONSTANT_Methodref:
    printf("CONSTANT_Methodref class_index=%d name_and_type_index=%d\n",
           constant->methodref.class_index,
           constant->methodref.name_and_type_index);
    break;
  case CONSTANT_InterfaceMethodref:
    printf("CONSTANT_InterfaceMethodref class_index=%d name_and_type_index=%d\n",
           constant->interfacemethodref.class_index,
           constant->interfacemethodref.name_and_type_index);
    break;
  case CONSTANT_String:
    printf("CONSTANT_String string_index=%d\n",
           constant->string.string_index);
    break;
  case CONSTANT_Integer:
    printf("CONSTANT_Integer bytes=%d\n",
           constant->integer.bytes);
    break;
  case CONSTANT_Float:
    printf("CONSTANT_Float bytes=%f\n",
           *(float *)(&constant->_float.bytes));
    break;
  case CONSTANT_Long:
    printf("CONSTANT_Long bytes=%l\n",
           constant->_long.bytes);
    break;
  case CONSTANT_Double:
    printf("CONSTANT_Double bytes=%f\n",
           *(double *)(&constant->_double.bytes));
    break;
  case CONSTANT_NameAndType:
    printf("CONSTANT_NameAndType name_index=%d descriptor_index=%d\n",
           constant->nameandtype.name_index,
           constant->nameandtype.descriptor_index);
    break;
  case CONSTANT_Utf8:
    printf("CONSTANT_Utf8 length=%d bytes=",
           constant->utf8.length);
    print__constant__utf8_string(constant);
    printf("\n");
    break;
  case CONSTANT_MethodHandle:
    printf("CONSTANT_MethodHandle reference_kind=%d reference_index=%d\n",
           constant->methodhandle.reference_kind,
           constant->methodhandle.reference_index);
    break;
  case CONSTANT_MethodType:
    printf("CONSTANT_MethodType descriptor_index=%d\n",
           constant->methodtype.descriptor_index);
    break;
  case CONSTANT_Dynamic:
    printf("CONSTANT_Dynamic bootstrap_method_attr_index=%d name_and_type_index=%d\n",
           constant->dynamic.bootstrap_method_attr_index,
           constant->dynamic.name_and_type_index);
    break;
  case CONSTANT_InvokeDynamic:
    printf("CONSTANT_InvokeDynamic bootstrap_method_attr_index=%d name_and_type_index=%d\n",
           constant->invokedynamic.bootstrap_method_attr_index,
           constant->invokedynamic.name_and_type_index);
    break;
  case CONSTANT_Module:
    printf("CONSTANT_Module name_index=%d\n",
           constant->module.name_index);
    break;
  case CONSTANT_Package:
    printf("CONSTANT_Package name_index=%d\n",
           constant->package.name_index);
    break;
  }
}

static void print_bootstrap_methods(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("num_bootstrap_methods: %d\n", attribute->bootstrap_methods->num_bootstrap_methods);
  prints(indent);
  printf("bootstrap methods:\n");
  for (int i = 0; i < attribute->bootstrap_methods->num_bootstrap_methods; i++) {
    prints(indent);
    printf("  bootstrap_method %d:\n", i);
    prints(indent);
    printf("    bootstrap_method_ref: %d\n", attribute->bootstrap_methods->bootstrap_methods[i].bootstrap_method_ref);
    prints(indent);
    printf("    num_bootstrap_arguments: %d\n", attribute->bootstrap_methods->bootstrap_methods[i].num_bootstrap_arguments);
    prints(indent);
    printf("    bootstrap_arguments:\n");
    for (int j = 0; j < attribute->bootstrap_methods->bootstrap_methods[i].num_bootstrap_arguments; j++) {
      prints(indent);
      printf("      bootstrap_argument %d: %d\n", j, attribute->bootstrap_methods->bootstrap_methods[i].bootstrap_arguments[j]);
    }
  }
}

static void print_nestmembers(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("number_of_classes: %d\n", attribute->nestmembers->number_of_classes);
  prints(indent);
  printf("classes:\n");
  for (int i = 0; i < attribute->nestmembers->number_of_classes; i++) {
    prints(indent);
    printf("  class %d:\n", i);
    prints(indent);
    prints("    ");
    print_constant(&constant_pool[attribute->nestmembers->classes[i] - 1]);
    int ix = constant_pool[attribute->nestmembers->classes[i] - 1].class.name_index;
    prints(indent);
    prints("      ");
    print_constant(&constant_pool[ix - 1]);
  }
}

static void print_nesthost(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("host_class_index: %d\n", attribute->nesthost->host_class_index);
}

static void print_constantvalue(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("constantvalue_index %d\n", attribute->constantvalue->constantvalue_index);


  struct constant * value = &constant_pool[attribute->constantvalue->constantvalue_index - 1];
  prints(indent);
  prints("  ");
  print_constant(value);
  if (value->tag == CONSTANT_String) {
    prints(indent);
    prints("    ");
    print_constant(&constant_pool[value->string.string_index - 1]);
  }
}

static void print_code(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  // print code
  prints(indent);
  printf("max_stack %d\n", attribute->code->max_stack);
  prints(indent);
  printf("max_locals %d\n", attribute->code->max_locals);
  prints(indent);
  printf("code_length %d\n", attribute->code->code_length);

  // dump code
  prints(indent);
  printf("code:\n");
  uint32_t pc = 0;
  while (pc < attribute->code->code_length) {
    prints(indent);
    prints("  ");
    pc = decode_print_instruction(attribute->code->code, pc);
  }


  prints(indent);
  printf("exception_table_length: %d\n", attribute->code->exception_table_length);
  prints(indent);
  printf("exceptions:\n");
  for (int i = 0; i < attribute->code->exception_table_length; i++) {
    prints(indent);
    printf("  exception %d:\n", i);
    prints(indent);
    printf("    start_pc: %d\n", attribute->code->exception_table[i].start_pc);
    prints(indent);
    printf("    end_pc: %d\n", attribute->code->exception_table[i].end_pc);
    prints(indent);
    printf("    handler_pc: %d\n", attribute->code->exception_table[i].handler_pc);
    prints(indent);
    printf("    catch_type: %d\n", attribute->code->exception_table[i].catch_type);
  }
  prints(indent);
  printf("attributes_count: %d\n", attribute->code->attributes_count);
  prints(indent);
  printf("attributes:\n");
  for (int i = 0; i < attribute->code->attributes_count; i++) {
    char indent2[string_length(indent) + 2 + 1];
    string_copy(indent2, indent);
    string_copy(indent2 + string_length(indent), "    ");
    prints(indent);
    printf("  attribute %d:\n", i);
    print_attribute(indent2, &attribute->code->attributes[i], constant_pool);
  }

}

static void print_line_number_table(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("line_number_table_length: %d\n", attribute->line_number_table->line_number_table_length);
  prints(indent);
  printf("line_number_table:\n");
  for (int i = 0; i < attribute->line_number_table->line_number_table_length; i++) {
    prints(indent);
    printf("  start_pc=%d line_number=%d\n",
           attribute->line_number_table->line_number_table[i].start_pc,
           attribute->line_number_table->line_number_table[i].line_number);
  }
}

static void print_exceptions(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("number_of_exceptions: %d\n", attribute->exceptions->number_of_exceptions);
  prints(indent);
  printf("exceptions:\n");
  for (int i = 0; i < attribute->exceptions->number_of_exceptions; i++) {
    prints(indent);
    printf("  exception_index_table[%d]: %d\n", i, attribute->exceptions->exception_index_table[i]);
    struct constant * class_constant = &constant_pool[attribute->exceptions->exception_index_table[i] - 1];
    assert(class_constant->tag == CONSTANT_Class);
    prints(indent);
    prints("    ");
    print_constant(class_constant);
    struct constant * class_name_constant = &constant_pool[class_constant->class.name_index - 1];
    assert(class_name_constant->tag == CONSTANT_Utf8);
    prints(indent);
    prints("      ");
    print_constant(class_name_constant);
  }
}

static void print_attribute(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  prints(indent);
  printf("attribute_name_index: %d\n", attribute->attribute_name_index);
  struct constant * attribute_name = &constant_pool[attribute->attribute_name_index - 1];
  prints(indent);
  prints("  ");
  print_constant(attribute_name);

  if (constant_equal(attribute_name, "ConstantValue")) {
    print_constantvalue(indent, attribute, constant_pool);
  } else if (constant_equal(attribute_name, "Code")) {
    print_code(indent, attribute, constant_pool);
  } else if (constant_equal(attribute_name, "BootstrapMethods")) {
    print_bootstrap_methods(indent, attribute, constant_pool);
  } else if (constant_equal(attribute_name, "NestHost")) {
    print_nesthost(indent, attribute, constant_pool);
  } else if (constant_equal(attribute_name, "NestMembers")) {
    print_nestmembers(indent, attribute, constant_pool);
  } else if (constant_equal(attribute_name, "LineNumberTable")) {
    print_line_number_table(indent, attribute, constant_pool);
  } else if (constant_equal(attribute_name, "Exceptions")) {
    print_exceptions(indent, attribute, constant_pool);
  }
}

void print_class_file(struct class_file * class_file)
{
  printf("magic %08x\n", class_file->magic);
  printf("minor_version %d\n", class_file->minor_version);
  printf("major_version %d\n", class_file->major_version);
  printf("constant_pool_count %d\n", class_file->constant_pool_count);

  printf("constants:\n");
  for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
    if (class_file->constant_pool[i].tag != 0) {
      printf("%4d: ", i + 1);
      print_constant(&class_file->constant_pool[i]);
    }
  }

  printf("access_flags %04x\n", class_file->access_flags);
  printf("this_class %d\n", class_file->this_class);
  printf("super_class %d\n", class_file->super_class);
  printf("interfaces_count %d\n", class_file->interfaces_count);

  printf("interfaces:\n");
  for (int i = 0; i < class_file->interfaces_count; i++) {
    printf("  interface %3d:\n", i);
    int interface_index = class_file->interfaces[i];
    prints("    ");
    struct constant * class_constant = &class_file->constant_pool[interface_index - 1];
    print_constant(class_constant);
    prints("      ");
    struct constant * class_name_constant = &class_file->constant_pool[class_constant->class.name_index - 1];
    print_constant(class_name_constant);
  }

  printf("fields_count %d\n", class_file->fields_count);
  printf("fields:\n");
  for (int i = 0; i < class_file->fields_count; i++) {
    printf("  field %d:\n", i);
    printf("    access_flags %d\n", class_file->fields[i].access_flags);
    printf("    name_index %d\n", class_file->fields[i].name_index);
    printf("      ");
    print_constant(&class_file->constant_pool[class_file->fields[i].name_index - 1]);
    printf("    descriptor_index %d\n", class_file->fields[i].descriptor_index);
    printf("      ");
    print_constant(&class_file->constant_pool[class_file->fields[i].descriptor_index - 1]);
    printf("    attributes_count %d\n", class_file->fields[i].attributes_count);
    printf("    attributes:\n");
    for (int j = 0; j < class_file->fields[i].attributes_count; j++) {
      printf("      attribute %d:\n", j);
      print_attribute("        ", &class_file->fields[i].attributes[j], class_file->constant_pool);
    }
  }

  printf("methods_count %d\n", class_file->methods_count);
  printf("methods:\n");
  for (int i = 0; i < class_file->methods_count; i++) {
    printf("  method %d:\n", i);
    printf("    access_flags %04x\n", class_file->methods[i].access_flags);
    printf("    name_index %d\n", class_file->methods[i].name_index);
    printf("      ");
    print_constant(&class_file->constant_pool[class_file->methods[i].name_index - 1]);
    printf("    descriptor_index %d\n", class_file->methods[i].descriptor_index);
    printf("      ");
    print_constant(&class_file->constant_pool[class_file->methods[i].descriptor_index - 1]);
    printf("    attributes_count %d\n", class_file->methods[i].attributes_count);
    printf("    attributes:\n");
    for (int j = 0; j < class_file->methods[i].attributes_count; j++) {
      printf("      attribute %d:\n", j);
      print_attribute("        ", &class_file->methods[i].attributes[j], class_file->constant_pool);
    }
  }


  printf("attributes_count %d\n", class_file->attributes_count);
  printf("attributes:\n");
  for (int i = 0; i < class_file->attributes_count; i++) {
    printf("  attribute %d:\n", i);
    print_attribute("    ", &class_file->attributes[i], class_file->constant_pool);
  }
}
