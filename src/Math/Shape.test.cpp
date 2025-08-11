#include <numbers>
#include <Math/Shape.hpp>
#include <Math/Transformations.hpp>
#include <MaterialCmp.hpp>
#include <Interactions.hpp>
#include <gtest/gtest.h>

Ray global_ray;

/**
 * @brief Concrete shape for testing some shape properties
 *
 */
class test_shape final : public Shape
{
public:
    std::vector<Intersection> local_intersect(const Ray &ray) const override
    {
        global_ray = ray;
        return std::vector<Intersection>();
    }

    Vector local_normal_at(const Point &point) const override
    {
        return Vector(point.x(), point.y(), point.z());
    }

    Ray &saved_ray = global_ray;
};

/*
Scenario: The default transformation
    Given s = test_shape()
    Then s.transform = identity_matrix
*/
TEST(ShapeTransform, hasDefaultTransformation)
{
    auto s = test_shape();
    ASSERT_EQ(s.transform, IDENTITY);
}

/*
Scenario: Assigning a transformation
    Given s = test_shape()
    When set_transform(s, translation(2, 3, 4))
    Then s.transform = translation(2, 3, 4)
*/
TEST(SphereTransform, changeTransformMatrix)
{
    auto s = test_shape();

    s.transform = translation(2, 3, 4);
    ASSERT_EQ(s.transform, translation(2, 3, 4));
}

/*
Scenario: The default material
    Given s = test_shape()
    When m = s.material
    Then m = material()
*/
TEST(ShapeMaterial, hasDefaultMaterial)
{
    auto s = test_shape();

    auto m = s.material;
    ASSERT_EQ(m, Material());
}

/*
Scenario: Assigning a material
    Given s = test_shape()
        And m = material()
        And m.ambient = 1
    When s.material = m
    Then s.material = m
*/
TEST(ShapeMaterial, assignMaterial)
{
    auto s = test_shape();
    auto m = Material();
    m.ambient = 1;

    s.material = m;
    ASSERT_EQ(s.material, m);
}

/*
Scenario: Intersecting a scaled shape with a ray
    Given r = ray(point(0, 0, -5), vector(0, 0, 1))
        And s = test_shape()
    When set_transform(s, scaling(2, 2, 2))
        And xs = intersect(s, r)
    Then s.saved_ray.origin = point(0, 0, -2.5)
        And s.saved_ray.direction = vector(0, 0, 0.5)
*/
TEST(ShapeIntersect, scaledShapeAndRay)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = test_shape();

    s.transform = scaling(2, 2, 2);
    auto xs = intersect(s, r);

    ASSERT_EQ(s.saved_ray.origin, Point(0, 0, -2.5));
    ASSERT_EQ(s.saved_ray.direction, Vector(0, 0, 0.5));
}

/*
Scenario: Intersecting a translated shape with a ray
    Given r = ray(point(0, 0, -5), vector(0, 0, 1))
        And s = test_shape()
    When set_transform(s, translation(5, 0, 0))
        And xs = intersect(s, r)
    Then s.saved_ray.origin = point(-5, 0, -5)
        And s.saved_ray.direction = vector(0, 0, 1)
*/
TEST(ShapeIntersect, translatedShapeAndRay)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = test_shape();

    s.transform = translation(5, 0, 0);
    auto xs = intersect(s, r);

    ASSERT_EQ(s.saved_ray.origin, Point(-5, 0, -5));
    ASSERT_EQ(s.saved_ray.direction, Vector(0, 0, 1));
}

/*
Scenario: Computing the normal on a translated shape
    Given s = test_shape()
    When set_transform(s, translation(0, 1, 0))
        And n = normal_at(s, point(0, 1.70711, -0.70711))
    Then n = vector(0, 0.70711, -0.70711)
*/
TEST(ShapeNormal, translatedShape)
{
    auto s = test_shape();

    s.transform = translation(0, 1, 0);
    auto n = s.normal_at(Point(0, 1.70711, -0.70711));

    ASSERT_EQ(n, Vector(0, 0.70711, -0.70711));
}

/*
Scenario: Computing the normal on a transformed shape
    Given s = test_shape()
        And m = scaling(1, 0.5, 1) * rotation_z(π/5)
    When set_transform(s, m)
        And n = normal_at(s, point(0, √2/2, -√2/2))
    Then n = vector(0, 0.97014, -0.24254)
*/
TEST(ShapeNormal, transformedShape)
{
    auto s = test_shape();
    auto m = scaling(1, 0.5, 1) * rotation_z(std::numbers::pi / 5);

    s.transform = m;
    auto n = s.normal_at(
        Point(0, std::numbers::sqrt2 / 2, -std::numbers::sqrt2 / 2));

    ASSERT_EQ(n, Vector(0, 0.97014, -0.24254));
}
