#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Light.hpp>
#include <scene/Material.hpp>

Color lighting(const Material &surface_mat, const Light &source,
               const Point &illuminated, const Vector &eye,
               const Vector &surface_norm);

#endif
