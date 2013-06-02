#include <cstdio>
#include <cstdarg>
#include <cstdlib>

#include "array_data_file.h"
#include "vertex_data_file.h"

typedef struct {
  int number_of_vertices;
  size_t size;
  GLenum type;
  int components;
} ADF_HEADER;

void create_array_data_file(const char *destination, const void *data, int number_of_vertices, size_t size, GLenum type, int components)
{
  ADF_HEADER header;

  header.number_of_vertices = number_of_vertices;
  header.size = size;
  header.type = type;
  header.components = components;

  FILE *file = fopen(destination, "w+b");
  if(file == NULL)  {
    fprintf(stderr, "Could not open %s for writting.\n", destination);

    exit(1);
  }

  if(fwrite(&header, sizeof(ADF_HEADER), 1, file) != 1)  {
    fprintf(stderr, "Could not write header to %s\n", destination);

    exit(1);
  }

  if(fwrite(data, size * components * number_of_vertices, 1, file) != 1)  {
    fprintf(stderr, "Could not write data to %s\n", destination);

    exit(1);
  }

  fclose(file);
}

void read_array_data_file(const char *source, void **data, int *number_of_vertices, size_t *size, GLenum *type, int *components)
{
  FILE *file = fopen(source, "rb");
  if(file == NULL)  {
    fprintf(stderr, "Could not open %s for reading\n", source);

    exit(1);
  }

  ADF_HEADER header;

  if(fread(&header, sizeof(ADF_HEADER), 1, file) != 1)  {
    fprintf(stderr, "Could not read header of %s\n", source);

    exit(1);
  }

  *number_of_vertices = header.number_of_vertices;
  *size = header.size;
  *type = header.type;
  *components = header.components;

  *data = malloc(header.size * header.components * header.number_of_vertices);
  if(*data == NULL)  {
    fprintf(stderr, "Could not allocate space for data at %p\n", source);

    exit(1);
  }

  if(fread(*data, header.size * header.components * header.number_of_vertices, 1, file) != 1)  {
    fprintf(stderr, "Could not read data from %s\n", source);

    exit(1);
  }

  fclose(file);
}

void create_VDF_from_ADFs(const char *destination, int number_of_arrays, GLenum draw_mode, ...)
{
  int attribute_locations[number_of_arrays];
  const char *files[number_of_arrays];

  void *data[number_of_arrays];

  va_list arrays;

  va_start(arrays, draw_mode);

  for(int i = 0; i <  number_of_arrays; i++)  {
    attribute_locations[i] = va_arg(arrays, int);
    files[i] = va_arg(arrays, const char*);
  }

  va_end(arrays);

  int number_of_vertices = 0, temp;

  size_t sizes[number_of_arrays];
  GLenum types[number_of_arrays];
  int components[number_of_arrays];

  for(int i = 0; i < number_of_arrays; i++) {
    read_array_data_file(files[i], &data[i], &temp, &sizes[i], &types[i], &components[i]);

    if(number_of_vertices == 0)
      number_of_vertices = temp;
    else if(number_of_vertices != temp) {
      fprintf(stderr, "The array_data_files do not have the same number of vertices.\n");

      for(int i = 0; i < number_of_arrays; i++)
        if(data[i] != NULL)
          free(data[i]);

      exit(1);
    }
  }

  create_vertex_data_file_arrays(destination, number_of_arrays, number_of_vertices, draw_mode, sizes, types, components, attribute_locations, data);

  for(int i = 0; i < number_of_arrays; i++)
    if(data[i] != NULL)
      free(data[i]);
}

