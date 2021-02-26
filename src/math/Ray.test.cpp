#include <gtest/gtest.h>
#include <math/Ray.hpp>

TEST(Ray, constructWithOriginAndDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
}
