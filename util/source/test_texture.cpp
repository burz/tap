#include <cstdio>
#include <cstdlib>

#include "gl_headers.h"
#include "file_interface/bit_field.h"

void test_texture(const char *file);

int main(int argc, char *argv[])
{
  test_texture(argv[1]);

  return 0;
}

void test_texture(const char *file)
{
  unsigned short width, height;
  size_t type_size;
  GLint internal_format;
  GLenum format, type;

  void *data;

  read_bit_field_file(file, &width, &height, &type_size, &internal_format, &format, &type, &data);

  printf("Testing: %s\n*************************************\n", file);
  printf("Width: %i\n", width);
  printf("Height: %i\n", height);
  printf("Type Size: %lu\n", type_size);
  printf("Internal Format: %i\n", internal_format);
  printf("Format: %i\n", format);
  printf("Type: %i\n\n", type);

  if(type == GL_UNSIGNED_SHORT || type == GL_UNSIGNED_SHORT_4_4_4_4) {
    unsigned short *us_data = (unsigned short *) data;

    printf("Data = { ");
    for(int i = 0; i < width * height; i++)
      printf("0x%hx, ", us_data[i]);
    printf("\b\b }\n");
  }
  else
    printf("Type %i not known.\n", type);

  free(data);
}

