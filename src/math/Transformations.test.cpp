#include <gtest/gtest.h>
#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Transformations.hpp>
#include <math/Vector.hpp>

TEST(Translation, getTranslationMatrix) {
  Matrix<4> translation = translate(1, 1, 1);
}

TEST(Translation, translatePoint) {
  Matrix<4> translation = translate(5, -3, 2);
  Point p(-3, 4, 5);
  ASSERT_EQ(translation * p, Point(2, 1, 7));
}

TEST(Translation, translateInReverseWithInverse) {
  Matrix<4> translation = translate(5, -3, 2);
  Point p(-3, 4, 5);
  ASSERT_EQ(inverse(translation) * p, Point(-8, 7, 3));
}

TEST(Translation, noChangeForTranslationOnVector) {
  Matrix<4> translation = translate(5, -3, 2);
  Vector v(-3, 4, 5);
  ASSERT_EQ(translation * v, v);
}

TEST(Scaling, getScalingMatrix) { Matrix<4> scaling = scale(1, 1, 1); }

TEST(Scaling, scalePoint) {
  Matrix<4> scaling = scale(2, 3, 4);
  Point p(-4, 6, 8);
  ASSERT_EQ(scaling * p, Point(-8, 18, 32));
}

TEST(Scaling, scaleVector) {
  Matrix<4> scaling = scale(2, 3, 4);
  Vector v(-4, 6, 8);
  ASSERT_EQ(scaling * v, Vector(-8, 18, 32));
}

TEST(Scaling, shrinkWithInverseScaling) {
  Matrix<4> scaling = scale(2, 3, 4);
  Vector v(-4, 6, 8);
  ASSERT_EQ(inverse(scaling) * v, Vector(-2, 2, 2));
}

TEST(Scaling, reflectByScalingWithNegativeValue) {
  Matrix<4> scaling = scale(-1, 1, 1);
  Point p(2, 3, 4);
  ASSERT_EQ(scaling * p, Point(-2, 3, 4));
}
