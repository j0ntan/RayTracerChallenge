#include <gtest/gtest.h>
#include <scene/Ray.hpp>

TEST(Ray, constructWithOriginAndDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
}

TEST(Ray, accessOrigin) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  r.origin;
}

TEST(Ray, matchGivenOrigin) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  ASSERT_EQ(r.origin, origin);
}

TEST(Ray, accessDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  r.direction;
}

TEST(Ray, matchGivenDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  ASSERT_EQ(r.direction, direction);
}

TEST(Ray, callPosition) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  position(r, 0);
}

TEST(Ray, getPointFromPosition) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  Point p = position(r, 0);
}

TEST(Ray, ComputePointFromDistance) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  ASSERT_EQ(position(r, 0), Point(2, 3, 4));
  ASSERT_EQ(position(r, 1), Point(3, 3, 4));
  ASSERT_EQ(position(r, -1), Point(1, 3, 4));
  ASSERT_EQ(position(r, 2.5), Point(4.5, 3, 4));
}
