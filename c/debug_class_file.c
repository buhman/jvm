#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "class_file.h"
#include "bytes.h"
#include "decode.h"
#include "debug_class_file.h"

void print_constant(struct constant * constant)
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
    printf("CONSTANT_Long high_bytes=%d low_bytes=%d\n",
           constant->_long.high_bytes,
           constant->_long.low_bytes);
    break;
  case CONSTANT_Double:
    printf("CONSTANT_Double high_bytes=%d low_bytes=%d\n",
           constant->_long.high_bytes,
           constant->_long.low_bytes);
    break;
  case CONSTANT_NameAndType:
    printf("CONSTANT_NameAndType %d %d\n",
           constant->nameandtype.name_index,
           constant->nameandtype.descriptor_index);
    break;
  case CONSTANT_Utf8:
    printf("CONSTANT_Utf8 length=%d bytes=",
           constant->utf8.length);
    for (int i = 0; i < constant->utf8.length; i++) {
      fputc(constant->utf8.bytes[i], stdout);
    }
    fputc('\n', stdout);
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

void print_attribute(const char * indent, struct attribute_info * attribute, struct constant * constant_pool)
{
  fputs(indent, stdout);
  printf("attribute_name_index: %d\n", attribute->attribute_name_index);
  struct constant * attribute_name = &constant_pool[attribute->attribute_name_index - 1];
  fputs(indent, stdout);
  fputs("  ", stdout);
  print_constant(attribute_name);

  if (bytes_equal(attribute_name->utf8.length, attribute_name->utf8.bytes, "ConstantValue")) {
    fputs(indent, stdout);
    printf("constantvalue_index %d\n", attribute->constantvalue->constantvalue_index);


    struct constant * value = &constant_pool[attribute->constantvalue->constantvalue_index - 1];
    fputs(indent, stdout);
    fputs("  ", stdout);
    print_constant(value);
    if (value->tag == CONSTANT_String) {
      fputs(indent, stdout);
      fputs("    ", stdout);
      print_constant(&constant_pool[value->string.string_index - 1]);
    }
  } else if (bytes_equal(attribute_name->utf8.length, attribute_name->utf8.bytes, "Code")) {
    // print code
    fputs(indent, stdout);
    printf("max_stack %d\n", attribute->code->max_stack);
    fputs(indent, stdout);
    printf("max_locals %d\n", attribute->code->max_locals);
    fputs(indent, stdout);
    printf("code_length %d\n", attribute->code->code_length);

    // dump code
    fputs(indent, stdout);
    printf("code:\n");
    uint32_t pc = 0;
    while (pc < attribute->code->code_length) {
      fputs(indent, stdout);
      fputs("  ", stdout);
      pc = decode_print_instruction(attribute->code->code, pc);
    }


    fputs(indent, stdout);
    printf("exception_table_length: %d\n", attribute->code->exception_table_length);
    fputs(indent, stdout);
    printf("exceptions:\n");
    for (int i = 0; i < attribute->code->exception_table_length; i++) {
      fputs(indent, stdout);
      printf("  exception %d:\n", i);
      fputs(indent, stdout);
      printf("    start_pc: %d\n", attribute->code->exception_table[i].start_pc);
      fputs(indent, stdout);
      printf("    end_pc: %d\n", attribute->code->exception_table[i].end_pc);
      fputs(indent, stdout);
      printf("    handler_pc: %d\n", attribute->code->exception_table[i].handler_pc);
      fputs(indent, stdout);
      printf("    catch_type: %d\n", attribute->code->exception_table[i].catch_type);
    }
    fputs(indent, stdout);
    printf("attributes_count: %d\n", attribute->code->attributes_count);
    fputs(indent, stdout);
    printf("attributes:\n");
    for (int i = 0; i < attribute->code->attributes_count; i++) {
      char indent2[strlen(indent) + 2 + 1];
      strcpy(indent2, indent);
      strcpy(indent2 + strlen(indent), "    ");
      fputs(indent, stdout);
      printf("  attribute %d:\n", i);
      print_attribute(indent2, &attribute->code->attributes[i], constant_pool);
    }
  } else if (bytes_equal(attribute_name->utf8.length, attribute_name->utf8.bytes, "BootstrapMethods")) {
    fputs(indent, stdout);
    printf("num_bootstrap_methods: %d\n", attribute->bootstrapmethods->num_bootstrap_methods);
    fputs(indent, stdout);
    printf("bootstrap methods:\n");
    for (int i = 0; i < attribute->bootstrapmethods->num_bootstrap_methods; i++) {
      fputs(indent, stdout);
      printf("  bootstrap_method %d:\n", i);
      fputs(indent, stdout);
      printf("    bootstrap_method_ref: %d\n", attribute->bootstrapmethods->bootstrap_methods[i].bootstrap_method_ref);
      fputs(indent, stdout);
      printf("    num_bootstrap_arguments: %d\n", attribute->bootstrapmethods->bootstrap_methods[i].num_bootstrap_arguments);
      fputs(indent, stdout);
      printf("    bootstrap_arguments:\n");
      for (int j = 0; j < attribute->bootstrapmethods->bootstrap_methods[i].num_bootstrap_arguments; j++) {
        fputs(indent, stdout);
        printf("      bootstrap_argument %d: %d\n", j, attribute->bootstrapmethods->bootstrap_methods[i].bootstrap_arguments[j]);
      }
    }
  } else if (bytes_equal(attribute_name->utf8.length, attribute_name->utf8.bytes, "NestHost")) {
    fputs(indent, stdout);
    printf("host_class_index: %d\n", attribute->nesthost->host_class_index);
  } else if (bytes_equal(attribute_name->utf8.length, attribute_name->utf8.bytes, "NestMembers")) {
    fputs(indent, stdout);
    printf("number_of_classes: %d\n", attribute->nestmembers->number_of_classes);
    fputs(indent, stdout);
    printf("classes:\n");
    for (int i = 0; i < attribute->nestmembers->number_of_classes; i++) {
      fputs(indent, stdout);
      printf("  class %d:\n", i);
      fputs(indent, stdout);
      fputs("    ", stdout);
      print_constant(&constant_pool[attribute->nestmembers->classes[i] - 1]);
      int ix = constant_pool[attribute->nestmembers->classes[i] - 1].class.name_index;
      fputs(indent, stdout);
      fputs("      ", stdout);
      print_constant(&constant_pool[ix - 1]);
    }
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
    printf("% 3d: ", i + 1);
    print_constant(&class_file->constant_pool[i]);
  }

  printf("access_flags %04x\n", class_file->access_flags);
  printf("this_class %d\n", class_file->this_class);
  printf("super_class %d\n", class_file->super_class);
  printf("interfaces_count %d\n", class_file->interfaces_count);

  printf("interfaces:\n");
  for (int i = 0; i < class_file->interfaces_count; i++) {
    printf("% 3d: %d\n", i + 1, class_file->interfaces[i]);
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
