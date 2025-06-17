#pragma once

#include <Math/Sphere.hpp>

/**
 * @brief Represents a single intersection between a ray and a sphere
 *
 */
struct Intersection
{
    /**
     * @brief The time of intersection
     *
     */
    double t;

    /**
     * @brief The object that was intersected
     *
     */
    const Sphere *object;
};
