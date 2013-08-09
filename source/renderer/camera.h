#pragma once

#include "bounding_volumes/bounding_sphere.h"
#include "math/math.h"

class Camera
{
public:
  Camera();
  Camera(const Vector3 position, const Vector3 forward, const Vector3 up);
  Camera(const Vector3 position, const Vector3 forward, const Vector3 up,
         float right, float top, float near, float far);
  Camera(float right, float top, float near, float far);
  Camera(const Vector3 position, const Vector3 forward, const Vector3 up,
         float left, float right, float bottom, float top, float near, float far);
  Camera(float left, float right, float bottom, float top, float near, float far);

  void set_position(const Vector3 position);
  void set_forward(const Vector3 forward);
  void set_up(const Vector3 up);

  void change_position(const Vector3 change);
  void change_position(float x, float y, float z);

  void get_view_matrix(Matrix4 destination) const;
  void get_projection_matrix(Matrix4 destination) const;

  bool is_culled(const Bounding_volume *volume) const;
protected:
  Vector3 position;
  Vector3 forward;
  Vector3 up;

  Plane frustum_far;
  Plane frustum_near;
  Plane frustum_bottom;
  Plane frustum_top;
  Plane frustum_left;
  Plane frustum_right;

  Bounding_sphere bounds;

  Matrix4 projection_matrix;
};

