#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <math/Sphere.hpp>

class Intersection {
public:
  explicit Intersection(const double t, const Sphere &sphere);

  bool operator==(const Intersection &rhs) const;
  bool operator!=(const Intersection &rhs) const;

  const double t;
  const Sphere &object;
};

#endif
