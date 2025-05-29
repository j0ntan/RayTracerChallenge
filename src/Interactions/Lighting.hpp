#pragma once

#include <Math/Vector.hpp>
#include <World/Material.hpp>
#include <World/PointLight.hpp>

/**
 * @brief Calculate the color that is reflected at a point on a surface with a
 * given light source
 *
 * @param material The material properties of the object being lit
 * @param light The light point source
 * @param point The point on the surface being lit
 * @param eye The eye vector, pointing from the lit point to the viewer
 * @param normal The normal vector at the lit point on the surface
 * @return Color The resulting color after applying lighting calculations
 */
Color lighting(const Material &material, const PointLight &light,
               const Point &point, const Vector eye_vector,
               const Vector &normal);
