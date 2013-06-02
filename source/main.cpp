#include <iostream>

#include "gl_headers.h"
#include "math/math.h"
#include "renderer/renderer.h"
#include "bounding_volumes/bounding_sphere.h"

int main(int argc, char *argv[])
{

  Vector3 pos1 = { 2.0, 0.0, 0.0 };
  Vector3 pos2 = { 4.0, 0.0, 0.0 };

  Bounding_sphere a(1.0);
  Bounding_sphere b(pos1, 0.5);
  Bounding_sphere c(pos2);

  std::cout << a.test_volume_intersection(&c) << std::endl;

  a.grow_to_contain(&b);

  std::cout << a.test_volume_intersection(&c) << std::endl;

  return 0;
}

