#include <graphics/Color.hpp>
#include <gtest/gtest.h>

TEST(Color, defaultConstruct) { Color c; }

TEST(Color, componentsDefaultedToZero) {
  Color c;
  ASSERT_FLOAT_EQ(c.red(), 0.0);
  ASSERT_FLOAT_EQ(c.green(), 0.0);
  ASSERT_FLOAT_EQ(c.blue(), 0.0);
}

TEST(Color, constructWithIntialValues) {
  Color c(.1f, .2f, .3f);
  ASSERT_EQ(c.red(), .1f);
  ASSERT_EQ(c.green(), .2f);
  ASSERT_EQ(c.blue(), .3f);
}

TEST(Color, copyConstruct) {
  Color c1(.1f, .2f, .3f);
  Color c2(c1);
  ASSERT_EQ(c1.red(), c2.red());
  ASSERT_EQ(c1.green(), c2.green());
  ASSERT_EQ(c1.blue(), c2.blue());
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
  c.red() = .1f;
  c.green() = .2f;
  c.blue() = .3f;
}

TEST(Color, assignFromColor) {
  Color c1, c2(1.0, 2.0, 3.0);
  c1 = c2;
  ASSERT_EQ(c1, c2);
}

TEST(Color, addWithAnotherColor) {
  Color c1(.1f, .2f, .3f), c2(.4f, .5f, .6f);
  Color c3(c1 + c2);
  ASSERT_FLOAT_EQ(c3.red(), .5f);
  ASSERT_FLOAT_EQ(c3.green(), .7f);
  ASSERT_FLOAT_EQ(c3.blue(), .9f);
}

TEST(Color, subtractWithAnotherColor) {
  Color c1(.1f, .2f, .3f), c2(.4f, .5f, .6f);
  Color c3(c2 - c1);
  ASSERT_FLOAT_EQ(c3.red(), .3f);
  ASSERT_FLOAT_EQ(c3.green(), .3f);
  ASSERT_FLOAT_EQ(c3.blue(), .3f);
}

TEST(Color, multiplyByScalar) {
  ASSERT_EQ(Color(0.2, 0.3, 0.4) * 2., Color(0.4, 0.6, 0.8));
  ASSERT_EQ(2 * Color(0.2, 0.3, 0.4), Color(0.4, 0.6, 0.8));
}

TEST(Color, multiplyWithAnotherColor) {
  Color c1(.1f, .2f, .3f), c2(.4f, .5f, .6f);
  Color c3(c1 * c2);
  ASSERT_FLOAT_EQ(c3.red(), .04f);
  ASSERT_FLOAT_EQ(c3.green(), .1f);
  ASSERT_FLOAT_EQ(c3.blue(), .18f);
}
