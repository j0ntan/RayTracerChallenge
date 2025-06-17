#include <Math/Shape.hpp>
#include <Math/Transformations.hpp>
#include <MaterialCmp.hpp>
#include <gtest/gtest.h>

/**
 * @brief Concrete shape for testing some shape properties
 *
 */
class test_shape : public Shape
{
    Vector normal_at(const Point &point) const override
    {
        return Vector();
    }
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
