#pragma once

#include "math/math.h"

class Bounding_volume
{
public:
  Bounding_volume();
  Bounding_volume(const Vector3 position);

  void set_position(const Vector3 position);
  void change_position(const Vector3 change);
  void change_position(float x, float y, float z);

  const float *get_position() const;
 
//  virtual int side(Plane plane) const = 0;

  virtual bool test_volume_intersection(const Bounding_volume *volume) const = 0;
//  virtual bool test_line_intersection(const float *origin, const float *direction) const = 0;

  virtual bool grow_to_contain(const Bounding_volume *volume) = 0;

  virtual void transform_by(const Matrix4 transformation) = 0;

//  virtual void support_mapping(float *result, float *direction) = 0;
protected:
  Vector3 position;
};

