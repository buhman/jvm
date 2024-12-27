#include <stdint.h>

#include "string.h"
#include "class_resolver.h"
#include "frame.h"
#include "printf.h"

#include "sh7091_scif.h"

#include "p/DreamcastVideo.class.h"
#include "java/lang/String.class.h"
#include "java/lang/Integer.class.h"
#include "java/lang/System.class.h"
#include "java/io/PrintStream.class.h"
#include "java/lang/Object.class.h"
#include "sega/dreamcast/holly/Holly.class.h"
#include "java/misc/Memory.class.h"

void main()
{
  scif_init(0);

  const uint8_t * class_file_buffers[] = {
    (const uint8_t *)&_binary_p_DreamcastVideo_class_start,
    (const uint8_t *)&_binary_java_lang_String_class_start,
    (const uint8_t *)&_binary_java_lang_Integer_class_start,
    (const uint8_t *)&_binary_java_lang_System_class_start,
    (const uint8_t *)&_binary_java_io_PrintStream_class_start,
    (const uint8_t *)&_binary_java_lang_Object_class_start,
    (const uint8_t *)&_binary_sega_dreamcast_holly_Holly_class_start,
    (const uint8_t *)&_binary_java_misc_Memory_class_start,
  };
  int class_file_buffers_length = (sizeof (class_file_buffers)) / (sizeof (class_file_buffers[0]));

  const uint8_t * main_class = (const uint8_t *)"p/DreamcastVideo";
  int main_class_length = string_length((const char *)main_class);

  int class_hash_table_length;
  struct hash_table_entry * class_hash_table = class_resolver_load_from_buffers(class_file_buffers,
                                                                                class_file_buffers_length,
                                                                                &class_hash_table_length);

  vm_start(class_hash_table_length,
           class_hash_table,
           main_class,
           main_class_length);
}
