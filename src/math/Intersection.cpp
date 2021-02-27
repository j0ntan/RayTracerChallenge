#include <math/Intersection.hpp>

Intersection::Intersection(const double t, const Sphere &sphere)
    : t{t}, obj{&sphere} {}

double Intersection::time() const { return t; }

const Sphere &Intersection::object() { return *obj; }

bool Intersection::operator==(const Intersection &rhs) const {
  return t == rhs.t && obj == rhs.obj;
}

bool Intersection::operator!=(const Intersection &rhs) const {
  return !(*this == rhs);
}

bool operator<(const Intersection &lhs, const Intersection &rhs) {
  return lhs.time() < rhs.time();
}
