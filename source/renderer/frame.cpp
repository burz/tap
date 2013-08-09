#include <cstring>

#include "frame.h"
#include "math/math.h"

Frame::Frame()
{
  position[0] = 0.0f;
  position[1] = 0.0f;
  position[2] = 0.0f;
  forward[0] = 0.0f;
  forward[1] = 0.0f;
  forward[2] = 1.0f;
  up[0] = 0.0f;
  up[1] = 1.0f;
  up[2] = 0.0f;
}

Frame::Frame(Vector3 position, Vector3 forward, Vector3 up)
{
  memcpy(this->position, position, sizeof(float) * 3);
  set_forward(forward);
  set_up(up);
}

void Frame::set_position(Vector3 position)
{
  memcpy(this->position, position, sizeof(float) * 3);
}

void Frame::set_forward(Vector3 forward)
{
  memcpy(this->forward, forward, sizeof(float) * 3);

  Math::normalize(this->forward);
}

void Frame::set_up(Vector3 up)
{
  memcpy(this->up, up, sizeof(float) * 3);

  Math::normalize(this->up);
}

void Frame::change_position(Vector3 translation)
{
  position[0] += translation[0];
  position[1] += translation[1];
  position[2] += translation[2];
}

void Frame::change_position(float x, float y, float z)
{
  position[0] += x;
  position[1] += y;
  position[2] += z;
}

void Frame::get_position(Vector3 destination) const
{
  memcpy(destination, position, sizeof(float) * 3);
}

void Frame::get_model_matrix(Matrix4 destination) const
{
  Vector3 cross;

  Math::cross_product(cross, up, forward);
  Math::normalize(cross);

  destination[3] = destination[7] = destination[11] = 0.0f;
  destination[15] = 1.0f;
  destination[12] = position[0];
  destination[13] = position[1];
  destination[14] = position[2];
  destination[0] = cross[0];
  destination[1] = cross[1];
  destination[2] = cross[2];
  destination[4] = up[0];
  destination[5] = up[1];
  destination[6] = up[2];
  destination[8] = forward[0];
  destination[9] = forward[1];
  destination[10] = forward[2];
}

