#include <gtest/gtest.h>
#include <primitives/Color.hpp>

TEST(Color, defaultConstruct) { Color c; }

TEST(Color, accessRedGreenBlueComponents) {
  Color c;
  c.red;
  c.green;
  c.blue;
}

TEST(Color, componentsDefaultedToZero) {
  Color c;
  ASSERT_FLOAT_EQ(c.red, 0.0);
  ASSERT_FLOAT_EQ(c.green, 0.0);
  ASSERT_FLOAT_EQ(c.blue, 0.0);
}

TEST(Color, constructWithIntialValues) { Color c(0.f, 0.f, 0.f); }

TEST(Color, matchComponentsToInitializationValue) {
  Color c(.1f, .2f, .3f);
  ASSERT_EQ(c.red, .1f);
  ASSERT_EQ(c.green, .2f);
  ASSERT_EQ(c.blue, .3f);
}
