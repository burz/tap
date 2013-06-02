#pragma once

#include "math.h"

typedef float Vector3[3];
typedef float Matrix4[16];

class Frame
{
public:
  Frame();
  Frame(Vector3 position, Vector3 forward, Vector3 up);

  void set_position(Vector3 position);
  void set_forward(Vector3 forward);
  void set_up(Vector3 up);

  void change_position(Vector3 translation);
  void change_position(float x, float y, float z);

  void get_position(Vector3 destination) const;

  void get_model_matrix(Matrix4 destination) const;
protected:
  Vector3 position;
  Vector3 forward;
  Vector3 up;
};

