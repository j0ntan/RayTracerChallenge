#pragma once

#include <Math/Matrix.hpp>

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
};
