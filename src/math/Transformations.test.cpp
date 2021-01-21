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

TEST(Rotation, getXRotationMatrix) { Matrix<4> x_rotation = rotate_x(1.0); }

TEST(Rotation, rotatePointAroundXAxis) {
  Point p(0, 1, 0);
  Matrix<4> half_quarter = rotate_x(PI / 4);
  Matrix<4> full_quarter = rotate_x(PI / 2);
  ASSERT_EQ(half_quarter * p, Point(0, sqrt(2) / 2, sqrt(2) / 2));
  ASSERT_EQ(full_quarter * p, Point(0, 0, 1));
}

TEST(Rotation, rotateInOppositeDirectionWithInverse) {
  Point p(0, 1, 0);
  Matrix<4> half_quarter = rotate_x(PI / 4);
  ASSERT_EQ(inverse(half_quarter) * p, Point(0, sqrt(2) / 2, -1 * sqrt(2) / 2));
}

TEST(Rotation, getYRotationMatrix) { Matrix<4> y_rotation = rotate_y(1.0); }

TEST(Rotation, rotatePointAroundYAxis) {
  Point p(0, 0, 1);
  Matrix<4> half_quarter = rotate_y(PI / 4);
  Matrix<4> full_quarter = rotate_y(PI / 2);
  ASSERT_EQ(half_quarter * p, Point(sqrt(2) / 2, 0, sqrt(2) / 2));
  ASSERT_EQ(full_quarter * p, Point(1, 0, 0));
}

TEST(Rotation, getZRotationMatrix) { Matrix<4> z_rotation = rotate_z(1.0); }

TEST(Rotation, rotatePointAroundZAxis) {
  Point p(0, 1, 0);
  Matrix<4> half_quarter = rotate_z(PI / 4);
  Matrix<4> full_quarter = rotate_z(PI / 2);
  ASSERT_EQ(half_quarter * p, Point(-1 * sqrt(2) / 2, sqrt(2) / 2, 0));
  ASSERT_EQ(full_quarter * p, Point(-1, 0, 0));
}
