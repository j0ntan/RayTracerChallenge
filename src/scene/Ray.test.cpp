#include <gtest/gtest.h>
#include <math/Transformations.hpp>
#include <scene/Ray.hpp>

TEST(RayConstructor, constructRay) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
}

TEST(RayOrigin, accessOrigin) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  r.ORIGIN;
}

TEST(RayConstructor, matchGivenOrigin) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  ASSERT_EQ(r.ORIGIN, origin);
}

TEST(RayDirection, accessDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  r.DIRECTION;
}

TEST(RayConstructor, matchGivenDirection) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  ASSERT_EQ(r.DIRECTION, direction);
}

TEST(RayPosition, callFunction) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  Point p = position(r, 0);
}

TEST(RayPosition, matchExpectedPoints) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  Point expected1(2, 3, 4), expected2(3, 3, 4), expected3(1, 3, 4),
      expected4(4.5, 3, 4);
  ASSERT_EQ(position(r, 0), expected1);
  ASSERT_EQ(position(r, 1), expected2);
  ASSERT_EQ(position(r, -1), expected3);
  ASSERT_EQ(position(r, 2.5), expected4);
}

TEST(TransformRay, callFunction) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 0));
  Matrix<4> m;
  Ray r2 = transform(r, m);
}

TEST(TransformRay, matchTranslatedRay) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix<4> translation = translate(3, 4, 5);

  Ray result_ray = transform(r, translation);
  Point expected_origin(4, 6, 8);
  Vector expected_direction(0, 1, 0);

  ASSERT_EQ(result_ray.ORIGIN, expected_origin);
  ASSERT_EQ(result_ray.DIRECTION, expected_direction);
}

TEST(TransformRay, matchScaledRay) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix<4> scaling_matrix = scale(2, 3, 4);

  Ray result_ray = transform(r, scaling_matrix);
  Point expected_origin(2, 6, 12);
  Vector expected_direction(0, 3, 0);

  ASSERT_EQ(result_ray.ORIGIN, Point(2, 6, 12));
  ASSERT_EQ(result_ray.DIRECTION, Vector(0, 3, 0));
}
