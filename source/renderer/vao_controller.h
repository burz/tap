#pragma once

#include "gl_headers.h"
#include "structures/hash_table.h"

typedef struct {
  GLuint handle;
  int number_of_vertices;
  GLenum draw_mode;
  int number_of_arrays;
  GLuint *buffers;
} array_record;

class VAO_controller
{
public:
  VAO_controller();
  ~VAO_controller();

  GLuint create_vertex_array(const char *vertex_data_file, int *number_of_vertices = 0, GLenum *draw_mode = 0);

  void delete_vertex_array(const char *file);
private:
  Hash_table<const char*, array_record> loaded_arrays;
};

