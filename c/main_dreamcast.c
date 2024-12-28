#include <stdint.h>

#include "string.h"
#include "class_resolver.h"
#include "frame.h"
#include "printf.h"

#include "sh7091_scif.h"

#include "classpath.h"
#include "example/DreamcastVideo2.class.h"

void main()
{
  scif_init(0);

  const uint8_t * class_file_buffers[] = {
    #include "classpath.inc.c"
    (const uint8_t *)&_binary_example_DreamcastVideo2_class_start,
  };
  int class_file_buffers_length = (sizeof (class_file_buffers)) / (sizeof (class_file_buffers[0]));

  const uint8_t * main_class = (const uint8_t *)"example/DreamcastVideo2";
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
