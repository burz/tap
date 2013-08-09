#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include "gl_headers.h"
#include "vertex_data_file.h"

/** 
 * Vertex Data File Structure:
 *
 * Header
 * --------
 * size_t sizes[ Header.number_of_arrays ];
 * GLenum types[ Header.number_of_arrays ];
 * int components[ Header.number_of_arrays ];
 * int attrib_locations[ Header.number_of_arrays ];
 * -----------
 * void data1[ sizes[ 1 ] ]
 * void data2[ sizes[ 2 ] ]
 * ...
 */

typedef struct {
  int number_of_arrays;
  int number_of_vertices;
  GLenum draw_mode;
} VDF_HEADER;

void create_vertex_data_file(const char *destination, int number_of_arrays,
                             int number_of_vertices, GLenum draw_mode, ...)
{
  size_t sizes[number_of_arrays];
  GLenum types[number_of_arrays];
  int components[number_of_arrays];
  int attribute_locations[number_of_arrays];
  void *data[number_of_arrays];

  va_list arrays;

  va_start(arrays, draw_mode);

  for(int i = 0; i < number_of_arrays; i++)  {
    sizes[i] = va_arg(arrays, size_t);
    types[i] = va_arg(arrays, GLenum);
    components[i] = va_arg(arrays, int);
    attribute_locations[i] = va_arg(arrays, int);
    data[i] = va_arg(arrays, void*);
  }

  va_end(arrays);

  create_vertex_data_file_arrays(destination, number_of_arrays, number_of_vertices,
                                 draw_mode, sizes, types, components,
                                 attribute_locations, data);
}

void create_vertex_data_file_arrays(const char *destination, int number_of_arrays,
                                    int number_of_vertices, GLenum draw_mode,
                                    size_t *sizes, GLenum *types, int *components,
                                    int *attribute_locations, void **data)
{
  FILE *file = fopen(destination, "w+b");
  if(file == NULL)  {
    fprintf(stderr, "Could not open %s for writting.\n", destination);

    exit(1);
  }

  VDF_HEADER header;

  header.number_of_arrays = number_of_arrays;
  header.number_of_vertices = number_of_vertices;
  header.draw_mode = draw_mode;

  if(fwrite(&header, sizeof(VDF_HEADER), 1, file) != 1)  {
        fprintf(stderr, "Writting header to %s failed.\n", destination);

        exit(1);
  }
  if(fwrite(sizes, sizeof(size_t) * number_of_arrays, 1, file) != 1)  {
        fprintf(stderr, "Writting sizes to %s failed.\n", destination);

        exit(1);
  }
  if(fwrite(types, sizeof(GLenum) * number_of_arrays, 1, file) != 1)  {
        fprintf(stderr, "Writting types to %s failed.\n", destination);

        exit(1);
  }
  if(fwrite(components, sizeof(int) * number_of_arrays, 1, file) != 1)  {
        fprintf(stderr, "Writting components to %s failed.\n", destination);

        exit(1);
  }
  if(fwrite(attribute_locations, sizeof(int) * number_of_arrays, 1, file) != 1)  {
        fprintf(stderr, "Writting attribute locations to %s failed.\n", destination);

        exit(1);
  }

  for(int i = 0; i < number_of_arrays; i++)
    if(fwrite(data[i], sizes[i] * components[i] * number_of_vertices, 1, file) != 1)  {
          fprintf(stderr, "Writting data to %s failed.\n", destination);

          exit(1);
    }

  fclose(file);
}

void **read_vertex_data_file(const char *vertex_data_file, int *number_of_arrays,
                             int *number_of_vertices, GLenum *draw_mode, size_t **sizes,
                             GLenum **types, int **components, int **attribute_locations)
{
  FILE *file = fopen(vertex_data_file, "rb");
  if(file == NULL)  {
    fprintf(stderr, "Could not load vertex data file: %s\n", vertex_data_file);

    exit(1);
  }

  VDF_HEADER header;

  if(fread(&header, sizeof(VDF_HEADER), 1, file) != 1)  {
    fprintf(stderr, "Could not read the vertex data file header from: %s\n",
                                                                   vertex_data_file);

    exit(1);
  }

  *number_of_arrays = header.number_of_arrays;
  *number_of_vertices = header.number_of_vertices;
  *draw_mode = header.draw_mode;

  void **data;
  
  *sizes = (size_t *) malloc(sizeof(size_t) * header.number_of_arrays);
  *types = (GLenum *) malloc(sizeof(GLenum) * header.number_of_arrays);
  *components = (int *) malloc(sizeof(int) * header.number_of_arrays);
  *attribute_locations = (int *) malloc(sizeof(int) * header.number_of_arrays);

  if(fread(*sizes, sizeof(size_t) * header.number_of_arrays, 1, file) != 1)  {
    fprintf(stderr, "Could not read the size data from: %s\n", vertex_data_file);

    free(*sizes);
    free(*types);
    free(*components);
    free(*attribute_locations);

    exit(1);
  }
  if(fread(*types, sizeof(GLenum) * header.number_of_arrays, 1, file) != 1)  {
    fprintf(stderr, "Could not read the type data from: %s\n", vertex_data_file);

    free(*sizes);
    free(*types);
    free(*components);
    free(*attribute_locations);

    exit(1);
  }
  if(fread(*components, sizeof(int) * header.number_of_arrays, 1, file) != 1)  {
    fprintf(stderr, "Could not read the component data from: %s\n", vertex_data_file);

    free(*sizes);
    free(*types);
    free(*components);
    free(*attribute_locations);

    exit(1);
  }
  if(fread(*attribute_locations, sizeof(int) * header.number_of_arrays, 1, file) != 1)  {
    fprintf(stderr, "Could not read the attribute location data from: %s\n",
                                                                      vertex_data_file);

    free(*sizes);
    free(*types);
    free(*components);
    free(*attribute_locations);

    exit(1);
  }

  data = (void **) malloc(sizeof(void *) * header.number_of_arrays);

  for(int i = 0; i < header.number_of_arrays; i++)  {
    data[i] = malloc((*sizes)[i] * (*components)[i] * header.number_of_vertices);
    if(data[i] == NULL)  {
      fprintf( stderr, "Not enough space to read in vertices.");

      for(int j = 0; j < i; j++)
        free(data[j]);
      free(*data);
      free(*sizes);
      free(*types);
      free(*components);
      free(*attribute_locations);

      exit(1);
    }

    if(fread(data[i], (*sizes)[i] * (*components)[i] * header.number_of_vertices, 1,
                                                                        file) != 1)  {
      fprintf(stderr, "Could not read the data from array %i in %s\n", i,
                                                                    vertex_data_file);

      for(int j = 0; j < i; j++)
        free(data[j]);
      free(*data);
      free(*sizes);
      free(*types);
      free(*components);
      free(*attribute_locations);

      exit(1);
    }
  }

  fclose(file);

  return data;
}

