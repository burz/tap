#include <cstdio>
#include <cstdlib>

#include "gl_headers.h"
#include "vao_controller.h"
#include "file_interface/vertex_data_file.h"
#include "structures/hash_functions.h"
#include "structures/compare_to.h"

VAO_controller::VAO_controller()
  : loaded_arrays(file_hash, string_compare_to)
{
}

VAO_controller::~VAO_controller()
{
  Hash_table_iterator<const char*, array_record> iterator = loaded_arrays.get_iterator();

  array_record record;

  while(iterator.has_next())  {
    iterator.next(&record);

    glDeleteBuffers(record.number_of_arrays, record.buffers);

    free(record.buffers);

#ifdef __APPLE__
    glDeleteVertexArraysAPPLE(1, &record.handle);
#else
    glDeleteVertexArrays(1, &record.handle);
#endif
  }
}

GLuint VAO_controller::create_vertex_array(const char *vertex_data_file,
                                           int *number_of_vertices, GLenum *draw_mode)
{
  array_record record;

  if(loaded_arrays.get(vertex_data_file, &record))  {
    if(number_of_vertices != 0)
      *number_of_vertices = record.number_of_vertices;
    if(draw_mode != 0)
      *draw_mode = record.draw_mode;

    return record.handle;
  }
  
  size_t *sizes;
  GLenum *types;
  int *components, *attribute_locations;

  void **data = read_vertex_data_file(vertex_data_file, &record.number_of_arrays,
                                      &record.number_of_vertices, &record.draw_mode,
                                      &sizes, &types, &components, &attribute_locations);

  record.handle = 0;

#ifdef __APPLE__
  glGenVertexArraysAPPLE(1, &record.handle);
#else
  glGenVertexArrays(1, &record.handle);
#endif

  if(record.handle == 0)  {
    fprintf(stderr, "Could not create vertex array object.");

    exit(1);
  }

  record.buffers = new GLuint[record.number_of_arrays];
  record.buffers[0] = 0;

  glGenBuffers(record.number_of_arrays, record.buffers);
  if(record.buffers[0] == 0)  {
    fprintf(stderr, "Could not create vertex buffers");

    exit(1);
  }

#ifdef __APPLE__
  glBindVertexArrayAPPLE(record.handle);
#else
  glBindVertexArray(record.handle);
#endif

  for(int i = 0; i < record.number_of_arrays; i++)  {
    glBindBuffer(GL_ARRAY_BUFFER, record.buffers[i]);
    glBufferData(GL_ARRAY_BUFFER, sizes[i] * components[i] * record.number_of_vertices,
                 data[i], GL_STATIC_DRAW);

    glEnableVertexAttribArray(attribute_locations[i]);
    glVertexAttribPointer(attribute_locations[i], components[i], types[i], GL_FALSE, 0,
                          (const GLvoid *) 0);
  }

#ifdef __APPLE__
  glBindVertexArrayAPPLE(0);
#else
  glBindVertexArray(0);
#endif

  for(int i = 0; i < record.number_of_arrays; i++)
    free(data[i]);
  free(data);
  free(sizes);
  free(types);
  free(components);
  free(attribute_locations);

  loaded_arrays.add(vertex_data_file, record);

  if(number_of_vertices != 0)
    *number_of_vertices = record.number_of_vertices;
  if(draw_mode != 0)
    *draw_mode = record.draw_mode;

  return record.handle;
}

void VAO_controller::delete_vertex_array(const char *file)
{
  array_record record;

  if(!loaded_arrays.get(file, &record))
    return;

  glDeleteBuffers(record.number_of_arrays, record.buffers);

  free(record.buffers);

#ifdef __APPLE__
  glDeleteVertexArraysAPPLE(1, &record.handle);
#else
  glDeleteVertexArrays(1, &record.handle);
#endif
}

