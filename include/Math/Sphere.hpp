#pragma once

#include <Math/Matrix.hpp>
#include <Math/Vector.hpp>
#include <World/Material.hpp>

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
};
