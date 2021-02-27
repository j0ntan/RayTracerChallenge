#include <math/Intersection.hpp>

Intersection::Intersection(const double t, const Sphere &sphere)
    : t{t}, object{sphere} {}

bool Intersection::operator==(const Intersection &rhs) const {
  return t == rhs.t && &object == &rhs.object;
}

bool Intersection::operator!=(const Intersection &rhs) const {
  return !(*this == rhs);
}
