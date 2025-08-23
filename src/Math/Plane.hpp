#pragma once

#include <Math/Shape.hpp>

/**
 * @brief A planar object used to build the ray tracer world
 *
 * The default plane is implemented as an infinitely thin, flat surface that
 * extends infinitely in the world's geometric xz-plane, passing through the
 * origin.
 *
 */
class Plane : public Shape
{
public:
    /**
     * @brief Destroy the plane object
     *
     */
    virtual ~Plane() = default;

    /**
     * @brief Plane-specific subclass implementation for calculating the normal
     * vector
     *
     * @param point The point on the shape's surface
     * @return Vector The normal vector at the point
     */
    virtual Vector local_normal_at(const Point &point) const override;

    /**
     * @brief Calculates the intersection of a ray and a plane
     *
     * @param ray The ray to intersect
     * @return std::vector<Intersection> The set of intersections, if any
     */
    virtual std::vector<Intersection>
    local_intersect(const Ray &ray) const override;
};
