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
