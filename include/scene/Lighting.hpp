#pragma once

#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Light.hpp>
#include <scene/Material.hpp>

/**
 * @brief Shades the world objects so that they appear three-dimensional
 *
 * @param surface_mat
 * @param source
 * @param illuminated
 * @param eye
 * @param surface_norm
 * @param in_shadow
 * @return Color
 */
Color lighting(const Material &surface_mat, const Light &source,
               const Point &illuminated, const Vector &eye,
               const Vector &surface_norm, bool in_shadow = false);
