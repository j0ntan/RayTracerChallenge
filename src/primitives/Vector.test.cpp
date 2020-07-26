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
