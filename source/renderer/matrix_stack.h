#pragma once

#include "math/math.h"

class Matrix_stack;

class Matrix_stack_node
{
  friend class Matrix_stack;
public:
  Matrix_stack_node();
  Matrix_stack_node(const Matrix4 matrix, Matrix_stack_node *next );
private:
  Matrix4 matrix;
  Matrix_stack_node *next;
};

class Matrix_stack
{
public:
  Matrix_stack();
  ~Matrix_stack();

  void push();
  void push_top();
  void push_matrix(const Matrix4 matrix);
  const float *top_matrix() const;
  void pop();

  void push_right_product(const Matrix4 matrix);
  void push_left_product(const Matrix4 matrix);

  void right_multiply(const Matrix4 matrix);
  void left_multiply(const Matrix4 matrix);

  void scale(float factor);
  void translate(const Vector3 vector);
  void translate(float x, float y, float z);
  void rotate(float x_angle, float y_angle, float z_angle);

  void perspective(float right, float top, float near, float far);
  void perspective(float left, float right, float bottom, float top, float near, float far);

  void get_normal_matrix(Matrix3 destination);
private:
  int size;
  Matrix_stack_node head;
};

