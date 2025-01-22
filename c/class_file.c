#include "assert.h"
#include "class_file.h"
#include "malloc.h"
#include "bytes.h"

struct attribute_info * attribute_info_parse(const uint8_t ** buf, int attribute_count, struct constant * constant_pool);

void * attribute_info_parse_info(const uint8_t * buf, struct attribute_info * attribute, struct constant * constant_pool)
{
  struct constant * attribute_name = &constant_pool[attribute->attribute_name_index - 1];
#ifdef DEBUG
  assert(attribute_name->tag == CONSTANT_Utf8);
#endif

  if (constant_equal(attribute_name, "ConstantValue")) {
    struct ConstantValue_attribute * constantvalue = malloc_class_arena((sizeof (struct ConstantValue_attribute)));
    constantvalue->constantvalue_index = parse_u2(&buf);
    return constantvalue;
  } else if (constant_equal(attribute_name, "Code")) {
    // parse Code
    struct Code_attribute * code = malloc_class_arena((sizeof (struct Code_attribute)));

    code->max_stack = parse_u2(&buf);
    code->max_locals = parse_u2(&buf);
    code->code_length = parse_u4(&buf);

    code->code = parse_bytes(&buf, code->code_length);
    code->exception_table_length = parse_u2(&buf);
    uint32_t exception_table_size = (sizeof (struct exception_table_entry)) * code->exception_table_length;
    code->exception_table = malloc_class_arena(exception_table_size);
    for (int i = 0; i < code->exception_table_length; i++) {
      // parse exception_table_entry
      code->exception_table[i].start_pc = parse_u2(&buf);
      code->exception_table[i].end_pc = parse_u2(&buf);
      code->exception_table[i].handler_pc = parse_u2(&buf);
      code->exception_table[i].catch_type = parse_u2(&buf);
    }
    code->attributes_count = parse_u2(&buf);

    code->attributes = attribute_info_parse(&buf, code->attributes_count, constant_pool);

    return code;
  } else if (constant_equal(attribute_name, "BootstrapMethods")) {
    // parse BootstrapMethods
    struct BootstrapMethods_attribute * bootstrap_methods = malloc_class_arena((sizeof (struct BootstrapMethods_attribute)));

    bootstrap_methods->num_bootstrap_methods = parse_u2(&buf);

    uint32_t bootstrap_methods_size = (sizeof (struct bootstrap_method)) * bootstrap_methods->num_bootstrap_methods;
    bootstrap_methods->bootstrap_methods = malloc_class_arena(bootstrap_methods_size);

    for (int i = 0; i < bootstrap_methods->num_bootstrap_methods; i++) {
      bootstrap_methods->bootstrap_methods[i].bootstrap_method_ref = parse_u2(&buf);
      bootstrap_methods->bootstrap_methods[i].num_bootstrap_arguments = parse_u2(&buf);

      uint32_t bootstrap_arguments_size = (sizeof (u2)) * bootstrap_methods->bootstrap_methods[i].num_bootstrap_arguments;
      bootstrap_methods->bootstrap_methods[i].bootstrap_arguments = malloc_class_arena(bootstrap_arguments_size);
      for (int j = 0; j < bootstrap_methods->bootstrap_methods[i].num_bootstrap_arguments; j++) {
        bootstrap_methods->bootstrap_methods[i].bootstrap_arguments[j] = parse_u2(&buf);
      }
    }

    return bootstrap_methods;
  } else if (constant_equal(attribute_name, "NestHost")) {
    struct NestHost_attribute * nesthost = malloc_class_arena((sizeof (struct NestHost_attribute)));
    nesthost->host_class_index = parse_u2(&buf);

    return nesthost;
  } else if (constant_equal(attribute_name, "NestMembers")) {
    struct NestMembers_attribute * nestmembers = malloc_class_arena((sizeof (struct NestMembers_attribute)));

    nestmembers->number_of_classes = parse_u2(&buf);
    uint32_t classes_size = (sizeof (u2)) * nestmembers->number_of_classes;
    nestmembers->classes = malloc_class_arena(classes_size);

    for (int i = 0; i < nestmembers->number_of_classes; i++) {
      nestmembers->classes[i] = parse_u2(&buf);
    }

    return nestmembers;
  } else if (constant_equal(attribute_name, "LineNumberTable")) {
    struct LineNumberTable_attribute * line_number_table = malloc_class_arena((sizeof (struct LineNumberTable_attribute)));
    line_number_table->line_number_table_length = parse_u2(&buf);

    uint32_t line_number_table_size = (sizeof (struct line_number_table)) * line_number_table->line_number_table_length;
    line_number_table->line_number_table = malloc_class_arena(line_number_table_size);

    for (int i = 0; i < line_number_table->line_number_table_length; i++) {
      line_number_table->line_number_table[i].start_pc = parse_u2(&buf);
      line_number_table->line_number_table[i].line_number = parse_u2(&buf);
    }
    return line_number_table;
  } else if (constant_equal(attribute_name, "Exceptions")) {
    struct Exceptions_attribute * exceptions = malloc_class_arena((sizeof (struct Exceptions_attribute)));
    exceptions->number_of_exceptions = parse_u2(&buf);
    uint32_t exceptions_size = (sizeof (u2)) * exceptions->number_of_exceptions;
    exceptions->exception_index_table = malloc_class_arena(exceptions_size);
    for (int i = 0; i < exceptions->number_of_exceptions; i++) {
      exceptions->exception_index_table[i] = parse_u2(&buf);
    }
    return exceptions;
  } else {
    return nullptr;
  }

  assert(false);
}

struct attribute_info * attribute_info_parse(const uint8_t ** buf, int attribute_count, struct constant * constant_pool)
{
  uint32_t attributes_size = (sizeof (struct attribute_info)) * attribute_count;
  struct attribute_info * attributes = malloc_class_arena(attributes_size);
  for (int i = 0; i < attribute_count; i++) {
    attributes[i].attribute_name_index = parse_u2(buf);
    attributes[i].attribute_length = parse_u4(buf);

    attributes[i].info = attribute_info_parse_info(*buf, &attributes[i], constant_pool);

    (*buf) += attributes[i].attribute_length;
  }
  return attributes;
}

struct class_file * class_file_parse(const uint8_t * buf)
{
  struct class_file * class_file = malloc_class_arena((sizeof (struct class_file)));

  class_file->magic = parse_u4(&buf);
  class_file->minor_version = parse_u2(&buf);
  class_file->major_version = parse_u2(&buf);
  class_file->constant_pool_count = parse_u2(&buf);

  uint32_t constant_pool_size = (sizeof (struct constant)) * (class_file->constant_pool_count - 1);
  class_file->constant_pool = malloc_class_arena(constant_pool_size);

  // parse constants
  for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    u1 tag = parse_u1(&buf);
    #ifdef DEBUG
    constant->tag = tag;
    #endif
    switch (tag) {
    case CONSTANT_Class:
      constant->class.name_index = parse_u2(&buf);
      break;
    case CONSTANT_Fieldref:             /* fall through */;
    case CONSTANT_Methodref:            /* fall through */;
    case CONSTANT_InterfaceMethodref:
      constant->fieldref.class_index = parse_u2(&buf);
      constant->fieldref.name_and_type_index = parse_u2(&buf);
      break;
    case CONSTANT_String:
      constant->string.string_index = parse_u2(&buf);
      break;
    case CONSTANT_Integer:              /* fall through */;
    case CONSTANT_Float:
      constant->integer.bytes = parse_u4(&buf);
      break;
    case CONSTANT_Long:                 /* fall through */;
    case CONSTANT_Double:
      {
        uint64_t high_bytes = parse_u4(&buf);
        uint64_t low_bytes = parse_u4(&buf);
        constant->_long.bytes = high_bytes << 32 | low_bytes;
        // long and double use two constant pool entries
        class_file->constant_pool[i + 1].tag = 0;
        i += 1;
      }
      break;
    case CONSTANT_NameAndType:
      constant->nameandtype.name_index = parse_u2(&buf);
      constant->nameandtype.descriptor_index = parse_u2(&buf);
      break;
    case CONSTANT_Utf8:
      constant->utf8.length = parse_u2(&buf);
      constant->utf8.bytes = parse_bytes(&buf, constant->utf8.length);
      break;
    case CONSTANT_MethodHandle:
      constant->methodhandle.reference_kind = parse_u1(&buf);
      constant->methodhandle.reference_index = parse_u2(&buf);
      break;
    case CONSTANT_MethodType:
      constant->methodtype.descriptor_index = parse_u2(&buf);
      break;
    case CONSTANT_Dynamic:              /* fall through */;
    case CONSTANT_InvokeDynamic:
      constant->dynamic.bootstrap_method_attr_index = parse_u2(&buf);
      constant->dynamic.name_and_type_index = parse_u2(&buf);
      break;
    case CONSTANT_Module:               /* fall through */;
    case CONSTANT_Package:
      constant->module.name_index = parse_u2(&buf);
      break;
    default:
      assert(false);
      break;
    }
  }

  class_file->access_flags = parse_u2(&buf);
  class_file->this_class = parse_u2(&buf);
  class_file->super_class = parse_u2(&buf);
  class_file->interfaces_count = parse_u2(&buf);

  // parse interfaces
  uint32_t interfaces_size = (sizeof (class_file->interfaces[0])) * class_file->interfaces_count;
  class_file->interfaces = malloc_class_arena(interfaces_size);
  for (int i = 0; i < class_file->interfaces_count; i++)
    class_file->interfaces[i] = parse_u2(&buf);

  // parse fields
  class_file->fields_count = parse_u2(&buf);
  uint32_t fields_size = (sizeof (struct field_info)) * class_file->fields_count;
  class_file->fields = malloc_class_arena(fields_size);
  for (int i = 0; i < class_file->fields_count; i++) {
    class_file->fields[i].access_flags = parse_u2(&buf);
    class_file->fields[i].name_index = parse_u2(&buf);
    class_file->fields[i].descriptor_index = parse_u2(&buf);
    class_file->fields[i].attributes_count = parse_u2(&buf);

    // parse attributes
    class_file->fields[i].attributes = attribute_info_parse(&buf, class_file->fields[i].attributes_count, class_file->constant_pool);
  }


  // parse methods
  class_file->methods_count = parse_u2(&buf);
  uint32_t methods_size = (sizeof (struct method_info)) * class_file->methods_count;
  class_file->methods = malloc_class_arena(methods_size);
  for (int i = 0; i < class_file->methods_count; i++) {
    class_file->methods[i].access_flags = parse_u2(&buf);
    class_file->methods[i].name_index = parse_u2(&buf);
    class_file->methods[i].descriptor_index = parse_u2(&buf);
    class_file->methods[i].attributes_count = parse_u2(&buf);

    // parse attributes
    class_file->methods[i].attributes = attribute_info_parse(&buf, class_file->methods[i].attributes_count, class_file->constant_pool);
  }

  // parse attributes
  class_file->attributes_count = parse_u2(&buf);
  class_file->attributes = attribute_info_parse(&buf, class_file->attributes_count, class_file->constant_pool);

  return class_file;
}
