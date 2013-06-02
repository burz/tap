#pragma once

#include "gl_headers.h"
#include "drivers/shaders/flat.h"

class Flat_box : public Flat
{
public:
  Flat_box();
  Flat_box( float *position, float *forward, float *up, float *color );

  virtual void load_vertices();

  virtual void draw();
private:
  static GLuint vertex_array;
};

