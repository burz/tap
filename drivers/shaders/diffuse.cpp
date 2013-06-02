#include <cstring>

#include "diffuse.h"
#include "math/math.h"
#include "renderer/shader_controller.h"
#include "renderer/matrix_stack.h"

extern Shader_controller shader_controller;

extern Matrix_stack modelview_stack;
extern Matrix_stack projection_stack;

GLuint Diffuse::shader = 0;

GLuint Diffuse::light_position_location = 0;
GLuint Diffuse::light_intensity_location = 0;
GLuint Diffuse::diffuse_reflectivity_location = 0;

GLuint Diffuse::modelview_location = 0;
GLuint Diffuse::normal_matrix_location = 0;
GLuint Diffuse::projection_location = 0;
GLuint Diffuse::modelviewprojection_location = 0;

Diffuse::Diffuse()
{
  light_position[0] = 0.0f;
  light_position[1] = 0.0f;
  light_position[2] = 1.0f;
  light_intensity[0] = 0.5f;
  light_intensity[1] = 0.5f;
  light_intensity[2] = 0.5f;
  diffuse_reflectivity[0] = 0.75f;
  diffuse_reflectivity[1] = 0.75f;
  diffuse_reflectivity[2] = 0.75f;
}

Diffuse::Diffuse(float *position, float *forward, float *up, float *light_position, float *light_intensity, float *diffuse_reflectivity)
  : Shader_driver(position, forward, up)
{
  memcpy(this->light_position, light_position, sizeof(float) * 3);
  memcpy(this->light_intensity, light_intensity, sizeof(float) * 3);
  memcpy(this->diffuse_reflectivity, diffuse_reflectivity, sizeof(float) * 3);
}

void Diffuse::load_shaders()
{
  if(shader != 0)
    return;

  shader = shader_controller.load_shaders_from_file("data/shaders/diffuse.vp", "data/shaders/diffuse.fp");

  glBindAttribLocation(shader, 0, "position");
  glBindAttribLocation(shader, 1, "normal");

  light_position_location = glGetUniformLocation(shader, "light_position");
  light_intensity_location = glGetUniformLocation(shader, "light_intensity");
  diffuse_reflectivity_location = glGetUniformLocation(shader, "diffuse_reflectivity");

  modelview_location = glGetUniformLocation(shader, "modelview_matrix");
  normal_matrix_location = glGetUniformLocation(shader, "normal_matrix");
  projection_location = glGetUniformLocation(shader, "projection_matrix");
  modelviewprojection_location = glGetUniformLocation(shader, "modelviewprojection_matrix");
}

void Diffuse::load_uniforms()
{
  glUniform3fv(light_position_location, 1, light_position);
  glUniform3fv(light_intensity_location, 1, light_intensity);
  glUniform3fv(diffuse_reflectivity_location, 1, diffuse_reflectivity);

  glUniformMatrix4fv(modelview_location, 1, GL_FALSE, modelview_stack.top_matrix());

  Matrix4 matrix;

  modelview_stack.get_normal_matrix(matrix);

  glUniformMatrix3fv(normal_matrix_location, 1, GL_FALSE, matrix);
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection_stack.top_matrix());

  Math::multiply_matrices(matrix, projection_stack.top_matrix(), modelview_stack.top_matrix());

  glUniformMatrix4fv(modelviewprojection_location, 1, GL_FALSE, matrix);
}

void Diffuse::set_light_position(float *light_position)
{
  memcpy(this->light_position, light_position, sizeof(float) * 3);
}

void Diffuse::set_light_intensity(float *light_intensity)
{
  memcpy(this->light_intensity, light_intensity, sizeof(float) * 3);
}

void Diffuse::set_diffuse_reflectivity(float *diffuse_reflectivity)
{
  memcpy(this->diffuse_reflectivity, diffuse_reflectivity, sizeof(float) * 3);
}

