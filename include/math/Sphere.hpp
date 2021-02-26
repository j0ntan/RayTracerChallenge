#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"

class Sphere {
public:
  Sphere() = default;
  explicit Sphere(const double radius, const Point &origin);
};

#endif
