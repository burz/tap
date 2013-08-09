#pragma once

#include "renderer/actor.h"

class Shader_driver : public Actor
{
public:
  Shader_driver() {};
  Shader_driver( float *position, float *forward, float *up )
    : Actor( position, forward, up ) {};

  virtual void load_shaders() = 0;
  virtual void load_vertices() = 0;

  virtual void load_uniforms() = 0;
  virtual void draw() = 0;
};

