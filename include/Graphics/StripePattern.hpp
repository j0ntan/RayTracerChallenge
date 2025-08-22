#pragma once

#include <Graphics/Color.hpp>
#include <Math/Point.hpp>
#include <Math/Sphere.hpp>

/**
 * @brief Represents a stripe pattern with two colors (a and b)
 *
 */
struct StripePattern
{
    Color a;
    Color b;
    Matrix<4> transform = IDENTITY;

    /**
     * @brief Select the color at a given point in the stripe pattern,
     * dependent on the x-coordinate only
     *
     * @param point The point in world-space where the color is queried
     * @return Color The color at the specified point
     */
    Color stripe_at(const Point &point) const;
};

/**
 * @brief todo
 *
 * @param pattern
 * @param object
 * @param point
 * @return Color
 */
Color stripe_at_object(const StripePattern &pattern, const Sphere &object,
                       const Point &point);
