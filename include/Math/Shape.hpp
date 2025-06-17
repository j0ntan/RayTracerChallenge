#pragma once

#include <vector>
#include <Math/Ray.hpp>
#include <World/Material.hpp>
#include <Interactions/Intersection.hpp>

/**
 * @brief Shape abstraction for ray tracer world objects
 *
 */
struct Shape
{
    /**
     * @brief Destroy the Shape object
     *
     */
    virtual ~Shape() = default;

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
     * @brief Create the unit normal vector at the given point for the shape
     *
     * This abstract method will be implemented by concrete shape subclasses.
     *
     * @param point The point on the shape's surface
     * @return Vector The normal vector at the point
     */
    virtual Vector normal_at(const Point &point) const = 0;

    /**
     * @brief Calculates the intersection of a ray and a shape
     *
     * This abstract method will be implemented by concrete shape subclasses.
     *
     * @param ray The ray to intersect
     * @return std::vector<Intersection> The set of intersections, if any
     */
    virtual std::vector<Intersection> local_intersect(const Ray &ray) const = 0;
};
