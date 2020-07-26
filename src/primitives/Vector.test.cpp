#include <gtest/gtest.h>
#include <primitives/Vector.hpp>

TEST(Vector, defaultConstruct) { Vector v; }

TEST(Vector, accessThreeSpatialComponents) {
  Vector v;
  v.x;
  v.y;
  v.z;
}

TEST(Vector, componentsDefaultedToZero) {
  Vector v;
  ASSERT_FLOAT_EQ(v.x, 0.0);
  ASSERT_FLOAT_EQ(v.y, 0.0);
  ASSERT_FLOAT_EQ(v.z, 0.0);
}

TEST(Vector, initialValueConstructed) { Vector v(1.0, 2.0, 3.0); }

TEST(Vector, componentsMatchInitializationInputs) {
  Vector v(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(v.x, 1.0);
  ASSERT_FLOAT_EQ(v.y, 2.0);
  ASSERT_FLOAT_EQ(v.z, 3.0);
}

TEST(Vector, copyConstruct) {
  Vector v1(1.0, 2.0, 3.0);
  Vector v2(v1);
}

TEST(Vector, copiedComponentsMatch) {
  Vector v1(1.0, 2.0, 3.0);
  Vector v2(v1);
  ASSERT_FLOAT_EQ(v1.x, v2.x);
  ASSERT_FLOAT_EQ(v1.y, v2.y);
  ASSERT_FLOAT_EQ(v1.z, v2.z);
}

TEST(Vector, callVectorComparator) {
  Vector v1, v2;
  v1 == v2;
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

TEST(Vector, addPointToVector) { Vector() + Point(); }

TEST(Vector, getPointByAddingPointToVector) { Point p = Vector() + Point(); }

TEST(Vector, addComponentsFromVectorPointAddition) {
  ASSERT_EQ(Vector(1.0, 2.0, 3.0) + Point(4.0, 5.0, 6.0), Point(5.0, 7.0, 9.0));
}

TEST(Vector, addVectorToPoint) {
  ASSERT_EQ(Point(4.0, 5.0, 6.0) + Vector(1.0, 2.0, 3.0), Point(5.0, 7.0, 9.0));
}

TEST(Vector, addTwoVectors) { Vector() + Vector(); }

TEST(Vector, getVectorFromVectorVectorAddition) {
  Vector v = Vector() + Vector();
}

TEST(Vector, addComponentsInVectorVectorAddition) {
  ASSERT_EQ(Vector(1.0, 2.0, 3.0) + Vector(4.0, 5.0, 6.0),
            Vector(5.0, 7.0, 9.0));
}

TEST(Vector, subtractTwoPoints) { Point() - Point(); }

TEST(Vector, getVectorFromPointPointsubtraction) {
  Vector v = Point() - Point();
}

TEST(Vector, subtractComponentsInPointPointSubtraction) {
  Point p1(4.0, 5.0, 6.0), p2(1.0, 2.0, 3.0);
  ASSERT_EQ(p1 - p2, Vector(3.0, 3.0, 3.0));
  ASSERT_EQ(p2 - p1, Vector(-3.0, -3.0, -3.0));
}

TEST(Vector, subtractVectorFromPoint) { Point() - Vector(); }

TEST(Vector, getPointFromPointVectorSubtraction) {
  Point p = Point() - Vector();
}

TEST(Vector, subtractComponentsInPointVectorSubtraction) {
  ASSERT_EQ(Point(4.0, 5.0, 6.0) - Vector(1.0, 2.0, 3.0), Point(3.0, 3.0, 3.0));
}

TEST(Vector, subtractTwoVectors) { Vector() - Vector(); }

TEST(Vector, getVectorFromVectorVectorSubtraction) {
  Vector v = Vector() - Vector();
}

TEST(Vector, subtractComponentsInVectorVectorSubtraction) {
  Vector v1(4.0, 5.0, 6.0), v2(1.0, 2.0, 3.0);
  ASSERT_EQ(v1 - v2, Vector(3.0, 3.0, 3.0));
  ASSERT_EQ(v2 - v1, Vector(-3.0, -3.0, -3.0));
}

TEST(Vector, negateVector) {
  Vector v(1.0, 0.0, 0.0);
  -v;
}

TEST(Vector, getVectorFromNegation) {
  Vector v1(1.0, 0.0, 0.0);
  Vector v2 = -v1;
}

TEST(Vector, negateComponentsOfNegatedVector) {
  Vector v(0.0, 1.0, 2.0);
  ASSERT_EQ(-v, Vector(0.0, -1.0, -2.0));
}
