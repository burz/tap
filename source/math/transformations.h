#pragma once

#include "matrices.h"

namespace Math
{
  void perspective_projection(Matrix4 destination, float left, float right, float bottom, float top, float near, float far);
  void symmetric_perspective_projection(Matrix4 destination, float right, float top, float near, float far);
}

