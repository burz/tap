#include <cstring>

#include "bounding_volume.h"

Bounding_volume::Bounding_volume()
{
  position[0] = 0.0f;
  position[1] = 0.0f;
  position[2] = 0.0f;
}

Bounding_volume::Bounding_volume(const Vector3 position)
{
  memcpy(this->position, position, sizeof(float) * 3);
}

void Bounding_volume::set_position(const Vector3 position)
{
  memcpy(this->position, position, sizeof(float) * 3);
}

void Bounding_volume::change_position(const Vector3 change)
{
  position[0] += change[0];
  position[1] += change[1];
  position[2] += change[2];
}

void Bounding_volume::change_position(float x, float y, float z)
{
  position[0] += x;
  position[1] += y;
  position[2] += z;
}

const float *Bounding_volume::get_position() const
{
  return position;
}

