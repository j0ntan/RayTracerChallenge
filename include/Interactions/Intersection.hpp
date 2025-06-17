#pragma once

/**
 * @brief Forward declare Sphere
 *
 */
class Sphere;

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
