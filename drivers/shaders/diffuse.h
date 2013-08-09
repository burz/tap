#pragma once

#include "gl_headers.h"
#include "shader_driver.h"
#include "math/math.h"

class Diffuse : public Shader_driver
{
public:
  Diffuse();
  Diffuse(float *position, float *forward, float *up, float *light_position,
          float *light_intensity, float *diffuse_reflectivity);

  virtual void load_shaders();
  virtual void load_vertices() = 0;

  virtual void load_uniforms();
  virtual void draw() = 0;

  void set_light_position(float *light_position);
  void set_light_intensity(float *light_intensity);
  void set_diffuse_reflectivity(float *diffuse_reflectivity);
protected:
  Vector3 light_position;
  Vector3 light_intensity;

  Vector3 diffuse_reflectivity;

  static GLuint shader;

  static GLuint light_position_location;
  static GLuint light_intensity_location;
  static GLuint diffuse_reflectivity_location;

  static GLuint modelview_location;
  static GLuint normal_matrix_location;
  static GLuint projection_location;
  static GLuint modelviewprojection_location;
};

