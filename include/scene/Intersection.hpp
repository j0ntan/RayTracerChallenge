#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <scene/Sphere.hpp>

class Intersection {
public:
  explicit Intersection(const double t, const Sphere &sphere);

  double time() const;
  const Sphere &object();

  bool operator==(const Intersection &rhs) const;
  bool operator!=(const Intersection &rhs) const;

private:
  double t;
  const Sphere *obj;
};

bool operator<(const Intersection &lhs, const Intersection &rhs);

#endif
