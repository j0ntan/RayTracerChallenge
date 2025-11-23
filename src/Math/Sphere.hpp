#pragma once

#include <Interactions/Intersection.hpp>
#include <Math/Shape.hpp>

/**
 * @brief A sphere object used to build the ray tracer world
 *
 */
struct Sphere : public Shape
{
    /**
     * @brief Destroy the Sphere object
     *
     */
    ~Sphere() = default;

    /**
     * @brief Calculates the intersection of a ray and a sphere
     *
     * @param ray The ray to intersect
     * @return std::vector<Intersection> The set of intersections, if any
     */
    std::vector<Intersection> local_intersect(const Ray &ray) const override;

    /**
     * @brief Sphere's implementation for calculating the normal vector
     *
     * @param point
     * @return Vector
     */
    virtual Vector local_normal_at(const Point &point) const override;
};

/**
 * @brief Create a sphere with glass-like properties, i.e. transparency and
 * refractive index of 1.0 and 1.5, respectively
 *
 * @return Sphere The glass sphere
 */
Sphere glass_sphere();
