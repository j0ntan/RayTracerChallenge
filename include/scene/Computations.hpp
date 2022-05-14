#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP

#include <math/Point.hpp>
#include <math/Vector.hpp>
#include <scene/Intersection.hpp>
#include <scene/Ray.hpp>
#include <scene/Sphere.hpp>

struct Computations {
  double t;
  const Sphere *object;
  Point point;
  Vector eyev;
  Vector normalv;
};

Computations prepare_computations(const Intersection &intersection,
                                  const Ray &ray);

#endif
