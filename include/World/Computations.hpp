#pragma once

#include <Math/Sphere.hpp>

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
    const Sphere *object;

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
};
