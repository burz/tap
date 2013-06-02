#include <cstdio>
#include <cstdlib>

#include "bit_field.h"

typedef struct {
  unsigned short width;
  unsigned short height;
  size_t type_size;
  GLint internal_format;
  GLenum format;
  GLenum type;
} BF_HEADER;

void create_bit_field_file(const char *destination, unsigned short width, unsigned short height, size_t type_size, GLint internal_format, GLenum format, GLenum type, void *data)
{
  BF_HEADER header;

  header.width = width;
  header.height = height;
  header.type_size = type_size;
  header.internal_format = internal_format;
  header.format = format;
  header.type = type;

  FILE *file = fopen(destination, "w+b");
  if(file == NULL)  {
    fprintf(stderr, "Could not open %s for writting.\n", destination);

    exit(1);
  }

  if( fwrite(&header, sizeof(BF_HEADER),  1, file) != 1)  {
    fprintf(stderr, "Writting to %s failed.\n", destination);

    exit(1);
  }
  
  if(fwrite(data, width * height * type_size,  1, file) != 1)  {
    fprintf(stderr, "Writting to %s failed.\n", destination);

    exit(1);
  }

  fclose( file );
}

void read_bit_field_file(const char *source, unsigned short *width, unsigned short *height, size_t *type_size, GLint *internal_format, GLenum *format, GLenum *type, void **data)
{
  FILE *file = fopen(source, "rb");
  if(file == NULL)  {
    fprintf(stderr, "Could not open %s for reading.\n", source);

    exit(1);
  }

  BF_HEADER header;

  if(fread(&header, sizeof(BF_HEADER), 1, file) != 1)  {
    fprintf(stderr, "Could not read the header of %s\n", source);

    exit(1);
  }

  if(width != NULL)
    *width = header.width;
  if(height != NULL)
    *height = header.height;
  if(type_size != NULL)
    *type_size = header.type_size;
  if(internal_format != NULL)
    *internal_format = header.internal_format;
  if(format != NULL)
    *format = header.format;
  if(type != NULL)
    *type = header.type;

  if(data == NULL)
    return;

  unsigned long image_size = header.height * header.width * header.type_size;

  *data = malloc(image_size);
  if(*data == NULL)  {
    fprintf(stderr, "Could not allocate enough space to load %s", source);

    exit(1);
  }

  if(fread(*data, image_size, 1, file) != 1)  {
    fprintf(stderr, "Could not read image data from %s", source);

    free(*data);

    exit(1);
  }

  fclose(file);
}

