#pragma once

#include "vectors.h"

typedef float Matrix2[4];
typedef float Matrix3[9];
typedef float Matrix4[16];

namespace Math
{
  void rotation_matrix(Matrix2 destination, float angle);
  void scalar_multiply2(Matrix2 matrix, float scalar);

  float determinant(const Matrix3 matrix);
  void inverse(Matrix3 destination, const Matrix3 source);
  void inverse(Matrix3 matrix);
  void transpose3(Matrix3 destination, const Matrix3 source);
  void transpose3(Matrix3 matrix);
  void scalar_multiply3(Matrix3 matrix, float scalar);

  void multiply_matrices(Matrix4 destination, const Matrix4 left, const Matrix4 right);
  void transpose4(Matrix4 destination, const Matrix4 source);
  void transpose4(Matrix4 matrix);
  void scalar_multiply4(Matrix4 matrix, float scalar);

  void scale(Matrix4 destination, float factor);
  void translate(Matrix4 destination, const Vector3 translation);

  void x_rotate(Matrix4 destination, float angle);
  void y_rotate(Matrix4 destination, float angle);
  void z_rotate(Matrix4 destination, float angle);
  void xyz_rotate(Matrix4 destination, float x_angle, float y_angle, float z_angle);
}

