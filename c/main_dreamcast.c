#include <stdint.h>

#include "string.h"
#include "class_resolver.h"
#include "frame.h"
#include "printf.h"

#include "sh7091_scif.h"

#include "p/Multiply.class.h"

void main()
{
  scif_init(0);

  const uint8_t * class_names[1];
  int class_names_length[1];

  class_names[0] = (const uint8_t *)"p/Multiply";
  class_names_length[0] = string_length((const char *)class_names[0]);

  const uint8_t * buffers[1];
  buffers[0] = (const uint8_t *)&_binary_p_Multiply_class_start;

  const uint8_t * main_class = class_names[0];
  int main_class_length = class_names_length[0];

  int length = (sizeof (class_names)) / (sizeof (class_names[0]));

  int class_hash_table_length;
  struct hash_table_entry * class_hash_table = class_resolver_load_from_buffers(class_names,
                                                                                class_names_length,
                                                                                buffers,
                                                                                length,
                                                                                &class_hash_table_length);

  vm_start(class_hash_table_length,
           class_hash_table,
           main_class,
           main_class_length);
}
