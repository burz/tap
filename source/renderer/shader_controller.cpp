#include <cstdio>
#include <cstdlib>

#include "gl_headers.h"
#include "shader_controller.h"
#include "structures/hash_functions.h"
#include "structures/compare_to.h"

bool load_source_file(char *destination, const char *file);

int program_contents_hash(program_contents contents);
int program_contents_compare_to(program_contents a, program_contents b);

Shader_controller::Shader_controller()
  : loaded_programs(program_contents_hash, program_contents_compare_to)
{
}

Shader_controller::~Shader_controller()
{
  Hash_table_iterator<program_contents, program_record> iterator = loaded_programs.get_iterator();

  program_record record;

  while(iterator.has_next())  {
    iterator.next(&record);

    glDeleteProgram(record.handle);

    glDeleteShader(record.vertex_shader);
    glDeleteShader(record.fragment_shader);
  }
}

GLuint Shader_controller::load_shaders_from_file(const char *vertex_file, const char *fragment_file)
{ 
  program_contents contents;

  contents.vertex_file = vertex_file;
  contents.fragment_file = fragment_file;

  program_record record;

  if(loaded_programs.get(contents, &record))
    return record.handle;

  record.vertex_shader = compile_shader(vertex_file, GL_VERTEX_SHADER);
  record.fragment_shader = compile_shader(fragment_file, GL_FRAGMENT_SHADER);

  if(record.vertex_shader == 0 || record.fragment_shader == 0)  {
    fprintf(stderr, "The program comprised of %s and %s failed to compile\n", vertex_file, fragment_file);

    exit(1);
  }

  record.handle = link_program(record.vertex_shader, record.fragment_shader);

  loaded_programs.add(contents, record);

  return record.handle;
}

void Shader_controller::delete_shader(const char *vertex_file, const char *fragment_file)
{
  program_contents contents;

  contents.vertex_file = vertex_file;
  contents.fragment_file = fragment_file;

  program_record record;

  if(!loaded_programs.get(contents, &record))
    return;

  glDeleteProgram(record.handle);

  glDeleteShader(record.vertex_shader);
  glDeleteShader(record.fragment_shader);
}

GLuint Shader_controller::link_program(GLuint vertex_shader, GLuint fragment_shader)
{
  GLuint program = glCreateProgram();

  if(program == 0)  {
    fprintf(stderr, "Could not create shader program.");

    return 0;
  }

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);

  if(status == GL_FALSE)  {
    fprintf(stderr, "Failed to link shader program!\n");

    GLint log_length;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

    if(log_length > 0)  {
      char *log = (char *) malloc(log_length);

      GLsizei temp;
      glGetProgramInfoLog(program, log_length, &temp, log);

      fprintf(stderr, "Program log:\n%s", log);

      free(log);
    }

    glDeleteProgram(program);

    return 0;
  }

  return program;
}

GLchar shader_code[MAX_SHADER_LENGTH];

GLuint Shader_controller::compile_shader(const char *file, GLenum type)
{
  GLuint shader = glCreateShader(type);

  if(shader == 0)  {
    fprintf(stderr, "Could not create vertex shader: %s with type %i", file, type);

    return 0;
  }

  if(!load_source_file(shader_code, file))
    return 0;

  const GLchar *code_array[] = { shader_code };
  glShaderSource(shader, 1, code_array, NULL);

  glCompileShader(shader);

  GLint result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

  if(result == GL_FALSE)  {
    fprintf(stderr, "Compilation of %s with type %i failed!\n", file, type);

    GLint log_length;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    if(log_length > 0)  {
      char *log = (char *) malloc(log_length);

      GLsizei temp;
      glGetShaderInfoLog(shader, log_length, &temp, log);

      fprintf(stderr, "Shader log:\n%s", log);

      free(log);
    }

    glDeleteShader(shader);

    return 0;
  }

  return shader;
}

bool load_source_file(char *destination, const char *file)
{
  GLuint shader_length = 0;
  FILE *f;

  f = fopen(file, "r");

  if(file == NULL)  {
    fprintf(stderr, "Shader %s failed to open.", file);

    return 0;
  }

  while(fgetc(f) != EOF)
    shader_length++;

  if(shader_length > MAX_SHADER_LENGTH)  {
    fprintf(stderr, "Shader source at %s is larger than the maximum allowed size: %i", file, MAX_SHADER_LENGTH);

    fclose(f);

    return 0;
  }

  rewind(f);

  fread(destination, 1, shader_length, f);

  destination[shader_length] = '\0';

  return 1;
}

int program_contents_hash(program_contents contents)
{
  int hash1 = file_hash(contents.vertex_file);
  int hash2 = file_hash(contents.fragment_file);

  return hash1 + (!hash2 << 8);
}

int program_contents_compare_to(program_contents a, program_contents b)
{
  return string_compare_to(a.vertex_file, b.vertex_file) == 0 && string_compare_to(a.fragment_file, b.fragment_file) == 0;
}

