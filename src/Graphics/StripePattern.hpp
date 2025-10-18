#pragma once

#include <Graphics/Color.hpp>
#include <Math/Point.hpp>
#include <Math/Matrix.hpp>

/**
 * @brief Forward declaration of `Shape` to avoid circular dependency
 *
 */
class Shape;

/**
 * @brief Represents a stripe pattern with two colors (a and b)
 *
 */
struct StripePattern
{
    /**
     * @brief The two colors that make up the stripe pattern
     *
     */
    Color a;
    Color b;

    /**
     * @brief The transform applied to the pattern
     *
     */
    Matrix<4> transform = {IDENTITY};

    /**
     * @brief Select the color at a given point in the stripe pattern
     *
     * @note Dependent on x-coordinate only
     *
     * @param point The point in world-space where the color is queried
     * @return Color The color at the specified point
     */
    Color stripe_at(const Point &point) const;

    /**
     * @brief Select the color at a given point on an object, taking into
     * account the transforms of both the object and the pattern
     *
     * @param object The object being shaded
     * @param world_point The point in world space
     * @return Color The color at the specified point on the object
     */
    Color stripe_at_object(const Shape &object, const Point &world_point) const;
};
