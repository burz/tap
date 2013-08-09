#include <cmath>
#include <cstring>

#include "matrices.h"
#include "math/math.h"

void Math::rotation_matrix(Matrix2 destination, float angle)
{
  destination[0] = destination[3] = cos(angle);
  destination[1] = sin(angle);
  destination[2] = -destination[1];
}

void Math::scalar_multiply2(Matrix2 matrix, float scalar)
{
  for(int i = 0; i < 4; i++)
    matrix[i] *= scalar;
}

float Math::determinant(const Matrix3 matrix)
{
  return matrix[0] * matrix[4] * matrix[8] + matrix[3] * matrix[7] * matrix[2] +
         matrix[6] * matrix[1] * matrix[5] - matrix[6] * matrix[4] * matrix[2] -
         matrix[3] * matrix[1] * matrix[8] - matrix[0] * matrix[7] * matrix[5];
}

void Math::inverse(Matrix3 destination, const Matrix3 source)
{
  float det = Math::determinant(source);

  destination[0] = (source[4] * source[8] - source[7] * source[5]) / det;
  destination[1] = -(source[3] * source[8] - source[6] * source[5]) / det;
  destination[2] = (source[3] * source[7] - source[4] * source[6]) / det;
  destination[3] = -(source[1] * source[8] - source[7] * source[2]) / det;
  destination[4] = (source[0] * source[8] - source[6] * source[2]) / det;
  destination[5] = -(source[0] * source[7] - source[6] * source[1]) / det;
  destination[6] = (source[1] * source[5] - source[4] * source[2]) / det;
  destination[7] = -(source[0] * source[5] - source[3] * source[2]) / det;
  destination[8] = (source[0] * source[4] - source[3] * source[1]) / det;
}

void Math::inverse(Matrix3 matrix)
{
  Matrix3 temp;

  memcpy(temp, matrix, sizeof(float) * 9);

  Math::inverse(matrix, temp);
}

void Math::transpose3(Matrix3 destination, const Matrix3 source)
{
  destination[1] = source[3];
    destination[2] = source[6];
    destination[3] = source[1];
    destination[5] = source[7];
    destination[6] = source[2];
    destination[7] = source[5];
}

void Math::transpose3(Matrix3 matrix)
{
  Matrix3 temp;

  memcpy(temp, matrix, sizeof(float) * 9);

  Math::transpose3(matrix, temp);
}

void Math::scalar_multiply3(Matrix3 matrix, float scalar)
{
  for(int i = 0; i < 9; i++)
    matrix[i] *= scalar;
}

void Math::multiply_matrices(Matrix4 destination, const Matrix4 left, const Matrix4 right)
{
  destination[0] = left[0] * right[0] + left[4] * right[1] +
                   left[8] * right[2] + left[12] * right[3];
  destination[1] = left[1] * right[0] + left[5] * right[1] +
                   left[9] * right[2] + left[13] * right[3];
  destination[2] = left[2] * right[0] + left[6] * right[1] +
                   left[10] * right[2] + left[14] * right[3];
  destination[3] = left[3] * right[0] + left[7] * right[1] +
                   left[11] * right[2] + left[15] * right[3];
  destination[4] = left[0] * right[4] + left[4] * right[5] +
                   left[8] * right[6] + left[12] * right[7];
  destination[5] = left[1] * right[4] + left[5] * right[5] +
                   left[9] * right[6] + left[13] * right[7];
  destination[6] = left[2] * right[4] + left[6] * right[5] +
                   left[10] * right[6] + left[14] * right[7];
  destination[7] = left[3] * right[4] + left[7] * right[5] +
                   left[11] * right[6] + left[15] * right[7];
  destination[8] = left[0] * right[8] + left[4] * right[9] +
                   left[8] * right[10] + left[12] * right[11];
  destination[9] = left[1] * right[8] + left[5] * right[9] +
                   left[9] * right[10] + left[13] * right[11];
  destination[10] = left[2] * right[8] + left[6] * right[9] +
                    left[10] * right[10] + left[14] * right[11];
  destination[11] = left[3] * right[8] + left[7] * right[9] +
                    left[11] * right[10] + left[15] * right[11];
  destination[12] = left[0] * right[12] + left[4] * right[13] +
                    left[8] * right[14] + left[12] * right[15];
  destination[13] = left[1] * right[12] + left[5] * right[13] +
                    left[9] * right[14] + left[13] * right[15];
  destination[14] = left[2] * right[12] + left[6] * right[13] +
                    left[10] * right[14] + left[14] * right[15];
  destination[15] = left[3] * right[12] + left[7] * right[13] +
                    left[11] * right[14] + left[15] * right[15];
}

void Math::transpose4(Matrix4 destination, const Matrix4 source)
{
  destination[1] = source[4];
  destination[2] = source[8];
  destination[3] = source[12];
  destination[4] = source[1];
  destination[6] = source[9];
  destination[7] = source[13];
  destination[8] = source[2];
  destination[9] = source[6];
  destination[11] = source[14];
  destination[12] = source[3];
  destination[13] = source[7];
  destination[14] = source[11];
}

void Math::transpose4(Matrix4 matrix)
{
  float temp[16];

  memcpy( temp, matrix, sizeof( float ) * 16 );

  Math::transpose4(matrix, temp);
}

void Math::scalar_multiply4(Matrix4 matrix, float scalar)
{
  for(int i = 0; i < 16; i++)
    matrix[i] *= scalar;
}

void Math::scale(Matrix4 destination, float factor)
{
  destination[1] = destination[2] = destination[3] = destination[4]
                 = destination[6] = destination[7] = 0.0f;
  destination[8] = destination[9] = destination[11] = destination[12]
                 = destination[13] = destination[14] = 0.0f;
  destination[15] = 1.0f;
  destination[0] = destination[5] = destination[10] = factor;
}

void Math::translate(Matrix4 destination, const Vector3 translation)
{
  destination[1] = destination[2] = destination[3] = destination[4]
                 = destination[6] = destination[7] = 0.0f;
  destination[8] = destination[9] = destination[11] = 0.0f;
  destination[0] = destination[5] = destination[10] = destination[15] = 1.0f;
  destination[12] = translation[0];
  destination[13] = translation[1];
  destination[14] = translation[2];
}

void Math::x_rotate(Matrix4 destination, float angle)
{
  destination[1] = destination[2] = destination[3] = destination[4]
                 = destination[7] = 0.0f;
  destination[8] = destination[11] = destination[12]
                 = destination[13] = destination[14] = 0.0f;
  destination[0] = destination[15] = 1.0f;
  destination[5] = destination[10] = cos(angle);
  destination[6] = sin(angle);
  destination[9] = -destination[6];
}

void Math::y_rotate(Matrix4 destination, float angle)
{
  destination[1] = destination[3] = destination[4] = destination[6]
                 = destination[7] = 0.0f;
  destination[9] = destination[11] = destination[12] = destination[13]
                 = destination[14] = 0.0f;
  destination[5] = destination[15] = 1.0f;
  destination[0] = destination[10] = cos(angle);
  destination[8] = sin(angle);
  destination[2] = -destination[8];
}

void Math::z_rotate(Matrix4 destination, float angle)
{
  destination[2] = destination[3] = destination[6] = destination[7]
                 = destination[8] = 0.0f;
  destination[9] = destination[11] = destination[12] = destination[13]
                 = destination[14] = 0.0f;
  destination[10] = destination[15] = 1.0f;
  destination[0] = destination[5] = cos(angle);
  destination[1] = sin(angle);
  destination[4] = -destination[1];
}

void Math::xyz_rotate(Matrix4 destination, float x_angle, float y_angle, float z_angle)
{
  Matrix4 rotation, temp;

  memcpy(destination, Math::identity_matrix4, sizeof(float) * 16);

  if(x_angle != 0)
    Math::x_rotate(destination, x_angle);

  if(y_angle != 0)  {
    memcpy(temp, destination, sizeof(float) * 16);
    Math::y_rotate(rotation, y_angle);
    Math::multiply_matrices(destination, rotation, temp);
  }

  if(z_angle != 0)  {
    memcpy(temp, destination, sizeof(float) * 16);
    Math::z_rotate(rotation, z_angle);
    Math::multiply_matrices(destination, rotation, temp);
  }
}

