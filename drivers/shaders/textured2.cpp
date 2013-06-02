#include "textured2.h"
#include "renderer/shader_controller.h"
#include "renderer/matrix_stack.h"
#include "math/math.h"

extern Shader_controller shader_controller;

extern Matrix_stack projection_stack;
extern Matrix_stack modelview_stack;

GLuint Textured2::shader = 0;
GLuint Textured2::modelviewprojection_location = 0;
GLuint Textured2::texture_location = 0;

Textured2::Textured2()
{
}

Textured2::Textured2(float *position, float *forward, float *up)
  : Shader_driver(position, forward, up)
{
}

void Textured2::load_uniforms()
{
  Matrix4 modelviewprojection_matrix;

  Math::multiply_matrices(modelviewprojection_matrix, projection_stack.top_matrix(), modelview_stack.top_matrix());

  glUniformMatrix4fv(modelviewprojection_location, 1, GL_FALSE, modelviewprojection_matrix);
}

void Textured2::load_shaders()
{
  if(shader != 0)
    return;

  shader = shader_controller.load_shaders_from_file("data/shaders/textured2.vp", "data/shaders/textured2.fp");

  glBindAttribLocation(shader, 0, "position");
  glBindAttribLocation(shader, 1, "texture_coordinates");

  modelviewprojection_location = glGetUniformLocation(shader, "modelviewprojection_matrix");
  texture_location = glGetUniformLocation(shader, "tex");
}

