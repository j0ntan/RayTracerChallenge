#include <cmath>
#include <gtest/gtest.h>
#include <math/Vector.hpp>

TEST(Vector, defaultConstruct) { Vector v; }

TEST(Vector, componentsDefaultedToZero) {
  Vector v;
  ASSERT_FLOAT_EQ(v.x, 0.0);
  ASSERT_FLOAT_EQ(v.y, 0.0);
  ASSERT_FLOAT_EQ(v.z, 0.0);
}

TEST(Vector, initialValueConstructed) {
  Vector v(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(v.x, 1.0);
  ASSERT_FLOAT_EQ(v.y, 2.0);
  ASSERT_FLOAT_EQ(v.z, 3.0);
}

TEST(Vector, copyConstruct) {
  Vector v1(1.0, 2.0, 3.0);
  Vector v2(v1);
  ASSERT_FLOAT_EQ(v1.x, v2.x);
  ASSERT_FLOAT_EQ(v1.y, v2.y);
  ASSERT_FLOAT_EQ(v1.z, v2.z);
}

TEST(Vector, equalToSelf) {
  Vector v;
  ASSERT_TRUE(v == v);
}

TEST(Vector, equalToCopy) {
  Vector v1, v2(v1);
  ASSERT_TRUE(v1 == v2);
}

TEST(Vector, notEqualToDifferentVector) {
  Vector v1, v2(1.0, 2.0, 3.0);
  ASSERT_FALSE(v1 == v2);
}

TEST(Vector, equalToVeryNearVector) {
  Vector v1, v2(0.0, 0.0, 0.000001);
  ASSERT_TRUE(v1 == v2);
}

TEST(Vector, changeCoordinates) {
  Vector v;
  v.x = 1.0;
  v.y = 2.0;
  v.z = 3.0;
}

TEST(Vector, assignFromVector) {
  Vector v1, v2(1.0, 2.0, 3.0);
  v1 = v2;
  ASSERT_EQ(v1, v2);
}

TEST(Vector, addPointToVector) {
  Point p = Vector(1.0, 2.0, 3.0) + Point(4.0, 5.0, 6.0);
  ASSERT_EQ(p, Point(5.0, 7.0, 9.0));
}

TEST(Vector, addVectorToPoint) {
  Point p = Point(4.0, 5.0, 6.0) + Vector(1.0, 2.0, 3.0);
  ASSERT_EQ(p, Point(5.0, 7.0, 9.0));
}

TEST(Vector, addTwoVectors) {
  Vector v = Vector(1.0, 2.0, 3.0) + Vector(4.0, 5.0, 6.0);
  ASSERT_EQ(v, Vector(5.0, 7.0, 9.0));
}

TEST(Vector, subtractTwoPoints) {
  Point p1(4.0, 5.0, 6.0), p2(1.0, 2.0, 3.0);
  Vector v1 = p1 - p2;
  Vector v2 = p2 - p1;
  ASSERT_EQ(v1, Vector(3.0, 3.0, 3.0));
  ASSERT_EQ(v2, Vector(-3.0, -3.0, -3.0));
}

TEST(Vector, subtractVectorFromPoint) {
  Point p = Point(4.0, 5.0, 6.0) - Vector(1.0, 2.0, 3.0);
  ASSERT_EQ(p, Point(3.0, 3.0, 3.0));
}

TEST(Vector, subtractTwoVectors) {
  Vector v1(4.0, 5.0, 6.0), v2(1.0, 2.0, 3.0);
  Vector v3 = v1 - v2;
  Vector v4 = v2 - v1;
  ASSERT_EQ(v3, Vector(3.0, 3.0, 3.0));
  ASSERT_EQ(v4, Vector(-3.0, -3.0, -3.0));
}

TEST(Vector, negateVector) {
  Vector v(0.0, 1.0, 2.0);
  Vector negative_v = -v;
  ASSERT_EQ(negative_v, Vector(0.0, -1.0, -2.0));
}

TEST(Vector, multiplyByScalar) {
  Vector v1 = Vector(1.0, 2.0, 3.0) * 0.5;
  Vector v2 = Vector(1.0, 2.0, 3.0) * -2.0;
  ASSERT_EQ(v1, Vector(0.5, 1.0, 1.5));
  ASSERT_EQ(v2, Vector(-2.0, -4.0, -6.0));
}

TEST(Vector, multiplyScalarByVector) {
  Vector v1 = 0.5 * Vector(1.0, 2.0, 3.0);
  Vector v2 = -2.0 * Vector(1.0, 2.0, 3.0);
  ASSERT_EQ(v1, Vector(0.5, 1.0, 1.5));
  ASSERT_EQ(v2, Vector(-2.0, -4.0, -6.0));
}

TEST(Vector, divideByScalar) {
  Vector v = Vector(2.0, 4.0, 6.0) / 2.0;
  ASSERT_EQ(v, Vector(1.0, 2.0, 3.0));
}

TEST(Vector, getMagnitude) {
  ASSERT_FLOAT_EQ(Vector(1, 0, 0).magnitude(), 1.0);
  ASSERT_FLOAT_EQ(Vector(0, 1, 0).magnitude(), 1.0);
  ASSERT_FLOAT_EQ(Vector(0, 0, 1).magnitude(), 1.0);
  ASSERT_FLOAT_EQ(Vector(1, 2, 3).magnitude(), std::sqrt(14));
  ASSERT_FLOAT_EQ(Vector(-1, -2, -3).magnitude(), std::sqrt(14));
}

TEST(Vector, normalize) {
  ASSERT_EQ(Vector(4, 0, 0).normalize(), Vector(1, 0, 0));
  ASSERT_EQ(Vector(1, 2, 3).normalize(),
            Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
  ASSERT_FLOAT_EQ(Vector(1, 2, 3).normalize().magnitude(), 1.0);
}

TEST(Vector, takeDotProduct) {
  double result = Vector(1, 2, 3).dot(Vector(2, 3, 4));
  ASSERT_FLOAT_EQ(result, 20.);
}

TEST(Vector, takeCrossProduct) {
  Vector v1 = Vector(1, 2, 3).cross(Vector(2, 3, 4));
  Vector v2 = Vector(2, 3, 4).cross(Vector(1, 2, 3));
  ASSERT_EQ(v1, Vector(-1, 2, -1));
  ASSERT_EQ(v2, Vector(1, -2, 1));
}
