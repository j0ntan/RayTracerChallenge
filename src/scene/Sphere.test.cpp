#include <cmath>
#include <gtest/gtest.h>
#include <scene/Sphere.hpp>
#include <scene/Transformations.hpp>

TEST(Sphere, defaultConstruct) { Sphere s; }

TEST(Sphere, constructWithRadiusAndOrigin) { Sphere s(1.0, Point()); }

TEST(Sphere, accessRadius) {
  const Sphere s;
  s.radius();
}

TEST(Sphere, defaultUnityRadius) {
  Sphere s;
  ASSERT_EQ(s.radius(), 1.0);
}

TEST(Sphere, radiusMatchesGivenValue) {
  const double RADIUS = 1.23;
  Sphere s(RADIUS, Point());
  ASSERT_EQ(s.radius(), RADIUS);
}

TEST(Sphere, accessOrigin) {
  const Sphere s;
  s.origin();
}

TEST(Sphere, defaultZeroOrigin) {
  Sphere s;
  ASSERT_EQ(s.origin(), Point(0, 0, 0));
}

TEST(Sphere, originMatchesGivenValue) {
  const Point ORIGIN(1, 2, 3);
  Sphere s(0, ORIGIN);
  ASSERT_EQ(s.origin(), ORIGIN);
}

TEST(Sphere, hasTransformation) {
  Sphere s;
  s.transformation();
}

TEST(Sphere, transformationIsMatrix) {
  Sphere s;
  Matrix<4> m = s.transformation();
}

TEST(Sphere, defaultTransformationIsIdentity) {
  Sphere s;
  ASSERT_EQ(s.transformation(), identity);
}

TEST(Sphere, setTransformationMatrix) {
  Sphere s;
  Matrix<4> m;
  s.set_transformation(m);
}

TEST(Sphere, transformationMatchesSetValue) {
  Sphere s;
  Matrix<4> m;
  s.set_transformation(m);
  ASSERT_EQ(s.transformation(), m);
}

TEST(NormalVector, getNormalAtPoint) {
  const Sphere s;
  s.normal(Point(1, 0, 0));
}

TEST(NormalVector, getNormalAsAVector) {
  const Sphere s;
  Vector n = s.normal(Point(1, 0, 0));
}

TEST(NormalVector, getNormalToPointOnXAxis) {
  const Sphere s;
  Vector n = s.normal(Point(1, 0, 0));
  ASSERT_EQ(n, Vector(1, 0, 0));
}

TEST(NormalVector, getNormalToPointOnYAxis) {
  const Sphere s;
  Vector n = s.normal(Point(0, 1, 0));
  ASSERT_EQ(n, Vector(0, 1, 0));
}

TEST(NormalVector, getNormalToPointOnZAxis) {
  const Sphere s;
  Vector n = s.normal(Point(0, 0, 1));
  ASSERT_EQ(n, Vector(0, 0, 1));
}

TEST(NormalVector, getNormalToNonAxialPoint) {
  const Sphere s;
  Vector n = s.normal(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  ASSERT_EQ(n, Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(NormalVector, isNormalized) {
  const Sphere s;
  Vector n = s.normal(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  ASSERT_EQ(n, n.normalize());
}

TEST(NormalVector, normalToTranslatedSphere) {
  Sphere s;
  s.set_transformation(translate(0, 1, 0));
  Vector n = s.normal(Point(0, 1 + sqrt(2) / 2, -sqrt(2) / 2));
  ASSERT_EQ(n, Vector(0, sqrt(2) / 2, -sqrt(2) / 2));
}

TEST(NormalVector, normalToTransformedSphere) {
  Sphere s;
  s.set_transformation(scale(1, 0.5, 1) * rotate_z(PI / 5));
  Vector n = s.normal(Point(0, sqrt(2) / 2, -sqrt(2) / 2));
  ASSERT_EQ(n, Vector(0, 0.97014, -0.24254));
}
