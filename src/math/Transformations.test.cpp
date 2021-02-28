#include <gtest/gtest.h>
#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Ray.hpp>
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

TEST(Shear, getShearMatrix) { Matrix<4> shearing = shear(1, 1, 1, 1, 1, 1); }

TEST(Shear, moveXInProportionToY) {
  Matrix<4> shearing = shear(1, 0, 0, 0, 0, 0);
  Point p(2, 3, 4);
  ASSERT_EQ(shearing * p, Point(5, 3, 4));
}

TEST(Shear, moveXInProportionToZ) {
  Matrix<4> shearing = shear(0, 1, 0, 0, 0, 0);
  Point p(2, 3, 4);
  ASSERT_EQ(shearing * p, Point(6, 3, 4));
}

TEST(Shear, moveYInProportionToX) {
  Matrix<4> shearing = shear(0, 0, 1, 0, 0, 0);
  Point p(2, 3, 4);
  ASSERT_EQ(shearing * p, Point(2, 5, 4));
}

TEST(Shear, moveYInProportionToZ) {
  Matrix<4> shearing = shear(0, 0, 0, 1, 0, 0);
  Point p(2, 3, 4);
  ASSERT_EQ(shearing * p, Point(2, 7, 4));
}

TEST(Shear, moveZInProportionToX) {
  Matrix<4> shearing = shear(0, 0, 0, 0, 1, 0);
  Point p(2, 3, 4);
  ASSERT_EQ(shearing * p, Point(2, 3, 6));
}

TEST(Shear, moveZInProportionToY) {
  Matrix<4> shearing = shear(0, 0, 0, 0, 0, 1);
  Point p(2, 3, 4);
  ASSERT_EQ(shearing * p, Point(2, 3, 7));
}

TEST(ChainingTransformations, applyTransformationsInSequence) {
  Point p(1, 0, 1);
  auto A = rotate_x(PI / 2);
  auto B = scale(5, 5, 5);
  auto C = translate(10, 5, 7);
  auto p2 = A * p;
  ASSERT_EQ(p2, Point(1, -1, 0));
  auto p3 = B * p2;
  ASSERT_EQ(p3, Point(5, -5, 0));
  auto p4 = C * p3;
  ASSERT_EQ(p4, Point(15, 0, 7));
}

TEST(ChainingTransformations, chainedTransformationsInReverseOrder) {
  Point p(1, 0, 1);
  auto A = rotate_x(PI / 2);
  auto B = scale(5, 5, 5);
  auto C = translate(10, 5, 7);
  auto T = C * B * A;
  ASSERT_EQ(T * p, Point(15, 0, 7));
}

TEST(TransformRay, callFunction) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 0));
  Matrix<4> m;
  transform(r, m);
}

TEST(TransformRay, returnsRay) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 0));
  Matrix<4> m;
  Ray r2 = transform(r, m);
}
