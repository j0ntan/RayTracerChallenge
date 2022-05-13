#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP

#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Sphere.hpp>

struct Computations {
  double t;
  const Sphere *object;
  Point point;
  Vector eyev;
  Vector normalv;
};

#endif
