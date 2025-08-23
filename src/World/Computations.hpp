#pragma once

#include <Math/Vector.hpp>

/**
 * @brief Forward declare Shape
 *
 */
class Shape;

/**
 * @brief Pprecomputed intersection data to be used in calculations
 *
 */
struct Computations
{
    /**
     * @brief The time of intersection
     *
     */
    double t;

    /**
     * @brief The object that was hit
     *
     */
    const Shape *object;

    /**
     * @brief The point of intersection in world coordinates
     *
     */
    Point point;

    /**
     * @brief The eye vector, pointing from the point of intersection towards
     * the ray's origin
     *
     */
    Vector eyev;

    /**
     * @brief The normal vector at the point of intersection, in world
     * coordinates
     *
     */
    Vector normalv;

    /**
     * @brief Flag indicating whether the intersection point is inside the
     * object
     *
     */
    bool inside;

    /**
     * @brief A point slightly above the point of intersection, for preventing
     * the acne effect
     *
     */
    Point over_point;
};
