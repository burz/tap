#pragma once

#include "bounding_volume.h"
#include "math/math.h"

class Bounding_sphere : public Bounding_volume
{
public:
  Bounding_sphere();
  Bounding_sphere(Vector3 position);
  Bounding_sphere(float radius);
  Bounding_sphere(const Vector3 position, float radius);

  virtual bool test_volume_intersection(const Bounding_volume *volume) const;

  virtual bool grow_to_contain(const Bounding_volume *volume);
  virtual void transform_by(const Matrix4 transformation);
protected:
  float radius;
};

