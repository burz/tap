#include "diffuse_box.h"
#include "renderer/vao_controller.h"
#include "renderer/matrix_stack.h"
#include "math/math.h"

extern VAO_controller vao_controller;

extern Matrix_stack modelview_stack;

GLuint Diffuse_box::vertex_array = 0;

Diffuse_box::Diffuse_box()
{
}

Diffuse_box::Diffuse_box(float *position, float *forward, float *up,
                         float *light_position, float *light_intensity,
                         float *diffuse_reflectivity)
  : Diffuse(position, forward, up, light_position, light_intensity, diffuse_reflectivity)
{
}

void Diffuse_box::load_vertices()
{
  if(vertex_array != 0)
    return;

  vertex_array = vao_controller.create_vertex_array("data/arrays/diffuse_box.vdf");
}

void Diffuse_box::draw()
{
  Matrix4 matrix;
  get_model_matrix(matrix);

  modelview_stack.push_right_product(matrix);

  glUseProgram(shader);

  load_uniforms();

#ifdef __APPLE__
  glBindVertexArrayAPPLE(vertex_array);
#else
  glBindVertexArray(vertex_array);
#endif

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#ifdef __APPLE__
  glBindVertexArrayAPPLE(0);
#else
  glBindVertexArray(0);
#endif

  modelview_stack.pop();
}

