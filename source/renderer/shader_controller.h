#pragma once

#include <cstdio>

#include "gl_headers.h"
#include "structures/hash_table.h"

#define MAX_SHADER_LENGTH 8192

typedef struct {
  const char *vertex_file;
  const char *fragment_file;
} program_contents;

typedef struct {
  GLuint handle;
  GLuint vertex_shader;
  GLuint fragment_shader;
} program_record;

class Shader_controller
{
public:
  Shader_controller();
  ~Shader_controller();

  GLuint load_shaders_from_file(const char *vertex_file, const char *fragment_file);

  void delete_shader(const char *vertex_file, const char *fragment_file);
private:
  GLuint link_program(GLuint vertex_shader, GLuint fragment_shader);
  GLuint compile_shader(const char *file, GLenum type);

  Hash_table<program_contents, program_record> loaded_programs;
};

