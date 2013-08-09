#pragma once

#include "vectors.h"

class Plane
{
public:
  Plane();
  Plane(Vector3 position, Vector3 normal);

  void set_position(Vector3 position);
  void set_normal(Vector3 normal);

  void get_position(Vector3 destination) const;
  void get_normal(Vector3 destination) const;
protected:
  float position[3];
  float normal[3];
};

