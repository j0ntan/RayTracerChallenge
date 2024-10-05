#include <cmath>

#include <gtest/gtest.h>

#include <math/Transformations.hpp>
#include <scene/Sphere.hpp>

TEST(SphereConstructor, defaultConstruct) { Sphere sphere; }

TEST(SphereConstructor, initializeParameter) {
  Material material{Color(1, 0, 0), 0.2, 0.8, 0.8, 190};
  Sphere sphere(material);
}

TEST(SphereRadius, accessRadius) {
  const Sphere sphere;
  double radius = sphere.RADIUS;
}

TEST(SphereRadius, matchDefaultRadius) {
  Sphere sphere;

  double expected = 1;
  ASSERT_EQ(sphere.RADIUS, expected);
}

TEST(SphereOrigin, accessOrigin) {
  const Sphere sphere;
  Point origin = sphere.ORIGIN;
}

TEST(SphereOrigin, matchDefaultOrigin) {
  Sphere sphere;

  Point expected(0, 0, 0);
  ASSERT_EQ(sphere.ORIGIN, expected);
}

TEST(SphereTransformation, getTransformation) {
  Sphere sphere;
  Matrix<4> transformation = sphere.transformation();
}

TEST(SphereTransformation, defaultTransformationIsIdentity) {
  Sphere sphere;
  ASSERT_EQ(sphere.transformation(), IDENTITY);
}

TEST(SphereTransformation, applyTransformation) {
  Sphere sphere;
  Matrix<4> new_transformation;
  sphere.apply_transformation(new_transformation);
}

TEST(SphereTransformation, matchAppliedTransformation) {
  Sphere sphere;
  Matrix<4> new_transformation = translate(1, 1, 1);
  sphere.apply_transformation(new_transformation);

  ASSERT_EQ(sphere.transformation(), new_transformation);
}

TEST(SphereNormal, getNormalAtPoint) {
  const Sphere sphere;
  Point point(1, 0, 0);
  Vector normal = sphere.normal_at(point);
}

TEST(SphereNormal, matchNormalToPointOnXAxis) {
  const Sphere sphere;
  Point point(1, 0, 0);

  Vector expected(1, 0, 0);
  ASSERT_EQ(sphere.normal_at(point), expected);
}

TEST(SphereNormal, getNormalToPointOnYAxis) {
  const Sphere sphere;
  Point point(0, 1, 0);

  Vector expected(0, 1, 0);
  ASSERT_EQ(sphere.normal_at(point), expected);
}

TEST(SphereNormal, getNormalToPointOnZAxis) {
  const Sphere sphere;
  Point point(0, 0, 1);

  Vector expected(0, 0, 1);
  ASSERT_EQ(sphere.normal_at(point), expected);
}

TEST(SphereNormal, getNormalToNonAxialPoint) {
  const Sphere sphere;
  Point point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);

  Vector expected(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
  ASSERT_EQ(sphere.normal_at(point), expected);
}

TEST(SphereNormal, isNormalized) {
  const Sphere sphere;
  Point point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
  Vector normal = sphere.normal_at(point);

  ASSERT_EQ(normal, normal.normalize());
}

TEST(SphereNormal, matchNormalToTranslatedSphere) {
  Sphere sphere;
  sphere.apply_transformation(translate(0, 1, 0));
  Point point(0, 1 + sqrt(2) / 2, -sqrt(2) / 2);

  Vector expected(0, sqrt(2) / 2, -sqrt(2) / 2);
  ASSERT_EQ(sphere.normal_at(point), expected);
}

TEST(SphereNormal, matchNormalToTransformedSphere) {
  Sphere sphere;
  sphere.apply_transformation(scale(1, 0.5, 1) * rotate_z(PI / 5));
  Point point(Point(0, sqrt(2) / 2, -sqrt(2) / 2));

  Vector expected(0, 0.97014, -0.24254);
  ASSERT_EQ(sphere.normal_at(point), expected);
}

TEST(SphereMaterial, accessMaterial) {
  Sphere sphere;
  Material material = sphere.material;
}

TEST(SphereMaterial, matchDefaultMaterial) {
  const Sphere sphere;

  Material expected = Material();
  ASSERT_EQ(sphere.material, expected);
}

TEST(SphereMaterial, modifyMaterialAttributes) {
  Sphere sphere;
  sphere.material.color = Color(1, 1, 0);
}

TEST(SphereIntersect, intersectRay) {
  Sphere sphere;
  std::vector<Intersection> intersections =
      sphere.intersect(Ray(Point(), Vector()));
}

TEST(SphereIntersect, matchTwoIntersectionPoints) {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere sphere;
  auto intersections = sphere.intersect(ray);

  double expected_t1 = 4, expected_t2 = 6;
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].time(), expected_t1);
  ASSERT_FLOAT_EQ(intersections[1].time(), expected_t2);
}

TEST(SphereIntersect, matchTangentIntersection) {
  Ray ray(Point(0, 1, -5), Vector(0, 0, 1));
  Sphere sphere;
  auto intersections = sphere.intersect(ray);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].time(), 5.0);
  ASSERT_FLOAT_EQ(intersections[1].time(), 5.0);
}

TEST(SphereIntersect, matchNoIntersectionOnRayMiss) {
  Ray ray(Point(0, 2, -5), Vector(0, 0, 1));
  Sphere sphere;
  auto intersections = sphere.intersect(ray);

  ASSERT_EQ(intersections.size(), 0);
}

TEST(SphereIntersect, intersectRayInsideSphere) {
  Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere sphere;
  auto intersections = sphere.intersect(ray);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].time(), -1.0);
  ASSERT_FLOAT_EQ(intersections[1].time(), 1.0);
}

TEST(SphereIntersect, intersectSphereBehindRay) {
  Ray ray(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere sphere;
  auto intersections = sphere.intersect(ray);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].time(), -6.0);
  ASSERT_FLOAT_EQ(intersections[1].time(), -4.0);
}

TEST(SphereIntersect, setTheObjectOnIntersection) {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere sphere;
  auto intersections = sphere.intersect(ray);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(&intersections[0].object(), &sphere);
  ASSERT_EQ(&intersections[1].object(), &sphere);
}

TEST(SphereIntersect, intersectScaledSphere) {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere sphere;
  sphere.apply_transformation(scale(2, 2, 2));
  auto intersections = sphere.intersect(ray);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0].time(), 3);
  ASSERT_EQ(intersections[1].time(), 7);
}

TEST(SphereIntersect, intersectTranslatedSphere) {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere sphere;
  sphere.apply_transformation(translate(5, 0, 0));
  auto intersections = sphere.intersect(ray);

  ASSERT_TRUE(intersections.empty());
}
