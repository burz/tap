#pragma once

#include "gl_headers.h"
#include "drivers/shaders/diffuse.h"

class Diffuse_cube : public Diffuse
{
public:
  Diffuse_cube();
  Diffuse_cube( float *position, float *forward, float *up, float *light_position, float *light_intensity, float *diffuse_reflectivity );

  virtual void load_vertices();

  virtual void draw();
private:
  static GLuint vertex_array;
};

