#include <graphics/Color.hpp>
#include <gtest/gtest.h>

TEST(ColorConstructor, createDefaultColor) { Color c; }

TEST(ColorAccessor, accessComponents) {
  Color c;
  double red = c.red();
  double green = c.green();
  double blue = c.blue();
}

TEST(ColorConstructor, matchZeroInitalComponentValues) {
  Color c;
  ASSERT_FLOAT_EQ(c.red(), 0.0);
  ASSERT_FLOAT_EQ(c.green(), 0.0);
  ASSERT_FLOAT_EQ(c.blue(), 0.0);
}

TEST(ColorConstructor, constructWithInitialValues) { Color c(.1f, .2f, .3f); }

TEST(ColorConstructor, matchInitialValues) {
  Color c(.1f, .2f, .3f);
  ASSERT_EQ(c.red(), .1f);
  ASSERT_EQ(c.green(), .2f);
  ASSERT_EQ(c.blue(), .3f);
}

TEST(ColorEqualityOperator, callOperator) {
  Color c;
  bool result = c == c;
}

TEST(ColorEqualityOperator, isEqualToItself) {
  Color c;
  ASSERT_TRUE(c == c);
}

TEST(ColorEqualityOperator, isEqualToCopy) {
  Color c1, c2(c1);
  ASSERT_TRUE(c1 == c2);
}

TEST(ColorEqualityOperator, isNotEqualToDifferentColor) {
  Color c1, c2(.1f, 0, 0);
  ASSERT_FALSE(c1 == c2);
}

TEST(ColorEqualityOperator, isEqualToNearlyIdenticalColor) {
  Color c1, c2(0, 0, 0.0000001);
  ASSERT_TRUE(c1 == c2);
}

TEST(ColorAccessor, changeRGBComponentValues) {
  Color c;

  ASSERT_FLOAT_EQ(c.red(), 0);
  ASSERT_FLOAT_EQ(c.green(), 0);
  ASSERT_FLOAT_EQ(c.blue(), 0);

  c.red() = .1f;
  c.green() = .2f;
  c.blue() = .3f;

  ASSERT_FLOAT_EQ(c.red(), .1f);
  ASSERT_FLOAT_EQ(c.green(), .2f);
  ASSERT_FLOAT_EQ(c.blue(), .3f);
}

TEST(ColorAssignmentOperator, callOperator) {
  Color c1, c2;
  c1 = c2;
}

TEST(ColorAssignmentOperator, matchAssignedColors) {
  Color c1, c2(1.0, 2.0, 3.0);

  ASSERT_NE(c1, c2);
  c1 = c2;
  ASSERT_EQ(c1, c2);
}

TEST(ColorAdditionOperator, callOperator) {
  Color c;
  Color result = c + c;
}

TEST(ColorAdditionOperator, matchAddedColor) {
  Color c1(.1f, .2f, .3f), c2(.4f, .5f, .6f);
  Color expected(.5f, .7f, .9f);
  ASSERT_EQ(c1 + c2, expected);
}

TEST(ColorSubtractionOperator, callOperator) {
  Color c;
  Color result = c - c;
}

TEST(ColorSubtractionOperator, matchSubtractedColor) {
  Color c1(.1f, .2f, .3f), c2(.4f, .5f, .6f);
  Color expected(.3f, .3f, .3f);
  ASSERT_EQ(c2 - c1, expected);
}

TEST(ColorMultiplyScalarOperator, callOperator) {
  Color c;
  Color result = c * 2.0;
  result = 2.0 * c;
}

TEST(ColorMultiplyScalarOperator, matchScalarMultiplicationValues) {
  Color c(0.2, 0.3, 0.4), expected(0.4, 0.6, 0.8);
  ASSERT_EQ(c * 2, expected);
  ASSERT_EQ(2 * c, expected);
}

TEST(ColorMultiplyColorOperator, callOperator) {
  Color c;
  Color result = c * c;
}

TEST(ColorMultiplyColorOperator, multiplyWithAnotherColor) {
  Color c1(.1f, .2f, .3f), c2(.4f, .5f, .6f);
  Color expected(.04f, .1f, .18f);
  ASSERT_EQ(c1 * c2, expected);
  ASSERT_EQ(c2 * c1, expected);
}
