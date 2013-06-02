#pragma once

#include "frame.h"

class Actor : public Frame
{
public:
  Actor() {}
  Actor( float *position, float *forward, float* up ) : Frame( position, forward, up ) {}

  virtual void load_shaders() = 0;
  virtual void load_vertices() = 0;

  virtual void draw() = 0;
};

