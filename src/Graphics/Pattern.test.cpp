#include <Graphics/Pattern.hpp>
#include <gtest/gtest.h>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>

/**
 * @brief Concrete pattern for testing some pattern properties
 *
 */
struct test_pattern final : public Pattern
{
    virtual ~test_pattern() = default;

    std::unique_ptr<Pattern> clone() const override
    {
        return std::make_unique<test_pattern>(*this);
    }

    Color pattern_at(const Point &point) const override
    {
        return Color(point.x(), point.y(), point.z());
    }
};

/*
Scenario: The default pattern transformation
    Given pattern = test_pattern()
    Then pattern.transform = identity_matrix
*/
TEST(PatternTransformation, hasDefaultTransform)
{
    auto pattern = test_pattern();
    ASSERT_EQ(pattern.transform, IDENTITY);
}

/*
Scenario: Assigning a transformation
    Given pattern = test_pattern()
    When set_pattern_transform(pattern, translation(1, 2, 3))
    Then pattern.transform = translation(1, 2, 3)
*/
TEST(PatternTransformation, assignTransformation)
{

    auto pattern = test_pattern();

    pattern.transform = translation(1, 2, 3);

    ASSERT_EQ(pattern.transform, translation(1, 2, 3));
}

/*
Scenario: A pattern with an object transformation
    Given shape = sphere()
        And set_transform(shape, scaling(2, 2, 2))
        And pattern = test_pattern()
    When c = pattern_at_shape(pattern, shape, point(2, 3, 4))
    Then c = color(1, 1.5, 2)
*/
TEST(PatternPatternAt, patternWithObjectTransformation)
{
    auto shape = Sphere();
    shape.transform = scaling(2, 2, 2);
    shape.material.pattern = std::make_unique<test_pattern>(test_pattern());

    auto c = shape.pattern_at(Point(2, 3, 4));

    ASSERT_EQ(c, Color(1, 1.5, 2));
}

/*
Scenario: A pattern with a pattern transformation
    Given shape = sphere()
        And pattern = test_pattern()
        And set_pattern_transform(pattern, scaling(2, 2, 2))
    When c = pattern_at_shape(pattern, shape, point(2, 3, 4))
    Then c = color(1, 1.5, 2)
*/
TEST(PatternPatternAt, patternWithPatternTransformation)
{
    auto shape = Sphere();
    shape.material.pattern = std::make_unique<test_pattern>(test_pattern());
    shape.material.pattern->transform = scaling(2, 2, 2);

    auto c = shape.pattern_at(Point(2, 3, 4));

    ASSERT_EQ(c, Color(1, 1.5, 2));
}

/*
Scenario: A pattern with both an object and a pattern transformation
    Given shape = sphere()
        And set_transform(shape, scaling(2, 2, 2))
        And pattern = test_pattern()
        And set_pattern_transform(pattern, translation(0.5, 1, 1.5))
    When c = pattern_at_shape(pattern, shape, point(2.5, 3, 3.5))
    Then c = color(0.75, 0.5, 0.25)
*/
TEST(PatternPatternAt, patternWithObjectAndPatternTransformation)
{
    auto shape = Sphere();
    shape.transform = scaling(2, 2, 2);
    shape.material.pattern = std::make_unique<test_pattern>(test_pattern());
    shape.material.pattern->transform = translation(0.5, 1, 1.5);

    auto c = shape.pattern_at(Point(2.5, 3, 3.5));

    ASSERT_EQ(c, Color(0.75, 0.5, 0.25));
}
