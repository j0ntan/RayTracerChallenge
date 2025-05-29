#pragma once

#include <Math/Point.hpp>
#include <Graphics/Color.hpp>

/**
 * @brief A point light source in the ray tracer world
 *
 */
struct PointLight
{
    Point position;
    Color intensity;
};
