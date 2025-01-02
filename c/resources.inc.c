#include "images/java_text.data.h"
#include "images/java_cup.data.h"
#include "images/java_powered.data.h"

#include "hash_table.h"
#include "assert.h"

struct resource {
  const uint8_t * name;
  int32_t name_length;
  const int32_t * buf;
  int32_t buf_length;
};

static struct resource resources[] = {
  /*
  {
    .name = (const uint8_t *)"images/java_text",
    .name_length = 16,
    .buf = (const int32_t *)&_binary_images_java_text_data_start,
    .buf_length = (int32_t)&_binary_images_java_text_data_size
  },
  {
    .name = (const uint8_t *)"images/java_cup",
    .name_length = 15,
    .buf = (const int32_t *)&_binary_images_java_cup_data_start,
    .buf_length = (int32_t)&_binary_images_java_cup_data_size
  },
  */
  {
    .name = (const uint8_t *)"images/java_powered",
    .name_length = 19,
    .buf = (const int32_t *)&_binary_images_java_powered_data_start,
    .buf_length = (int32_t)&_binary_images_java_powered_data_size
  },
};

static int resources_length = (sizeof (resources)) / (sizeof (resources[0]));

static uint32_t find_resource(const uint8_t * name, int32_t name_length)
{
  for (int i = 0; i < resources_length; i++) {
    struct resource * resource = &resources[i];
    if (resource->name_length != name_length)
      continue;
    if (hash_table_key_equal(resource->name, name, name_length)) {
      //debugf("resource match: ");
      //print_string((const char *)name, name_length);
      //debugc('\n');
      uint32_t buf = (uint32_t)resource->buf;
      // alignment check
      assert((resource->buf_length & (~3)) == resource->buf_length);
      assert((buf & ~(3)) == buf);
      return buf;
    }
  }
  return 0;
}
