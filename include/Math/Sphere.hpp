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
     * @brief Create the unit normal vector at the given point on the sphere
     *
     * @param point The point on the sphere's surface
     * @return Vector The normal vector at the point
     */
    Vector normal_at(const Point &point) const override;

    /**
     * @brief Calculates the intersection of a ray and a sphere
     *
     * @param ray The ray to intersect
     * @return std::vector<Intersection> The set of intersections, if any
     */
    std::vector<Intersection> local_intersect(const Ray &ray) const override;
};
