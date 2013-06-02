#pragma once

typedef float Vector3[3];

namespace Math
{
  float abs(const Vector3 a, const Vector3 b);
  float length(const Vector3 vector);
  void normalize(Vector3 vector);
  void cross_product(Vector3 destination, const Vector3 a, const Vector3 b);
}

