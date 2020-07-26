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
