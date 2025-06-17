#pragma once

#include <vector>
#include <Math/Ray.hpp>
#include <World/Material.hpp>
#include <Interactions/Intersection.hpp>

/**
 * @brief A sphere object used to build the ray tracer world
 *
 */
struct Sphere
{
    /**
     * @brief The transform applied to the sphere
     *
     */
    Matrix<4> transform = {IDENTITY};

    /**
     * @brief The surface material of the sphere
     *
     */
    Material material{};

    /**
     * @brief Create the unit normal vector at the given point on the sphere
     *
     * @param point The point on the sphere's surface
     * @return Vector The normal vector at the point
     */
    Vector normal_at(const Point &point) const;

    /**
     * @brief Calculates the intersection of a ray and a sphere
     *
     * @param ray The ray to intersect
     * @return std::vector<Intersection> The set of intersections, if any
     */
    std::vector<Intersection> local_intersect(const Ray &ray) const;
};
