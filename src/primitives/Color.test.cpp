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

TEST(Color, copyConstruct) {
  Color c1;
  Color c2(c1);
}

TEST(Color, matchCopiedColorComponents) {
  Color c1(.1f, .2f, .3f);
  Color c2(c1);
  ASSERT_EQ(c1.red, c2.red);
  ASSERT_EQ(c1.green, c2.green);
  ASSERT_EQ(c1.blue, c2.blue);
}

TEST(Color, compareForEquality) {
  Color c1, c2;
  c1 == c2;
}

TEST(Color, equalToItself) {
  Color c;
  ASSERT_TRUE(c == c);
}

TEST(Color, equalToCopy) {
  Color c1, c2(c1);
  ASSERT_TRUE(c1 == c2);
}

TEST(Color, notEqualToDiffentColor) {
  Color c1, c2(.1f, 0, 0);
  ASSERT_FALSE(c1 == c2);
}

TEST(Color, equalToNearlyIdenticalColor) {
  Color c1, c2(0, 0, 0.0000001);
  ASSERT_TRUE(c1 == c2);
}

TEST(Color, changeRGBComponentValues) {
  Color c;
  c.red = .1f;
  c.green = .2f;
  c.blue = .3f;
}
