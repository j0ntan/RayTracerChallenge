#include <scene/Intersection.hpp>

Intersection::Intersection(const double time, const Sphere &sphere)
    : time_{time}, object_{&sphere} {}

double Intersection::time() const { return time_; }

const Sphere &Intersection::object() const { return *object_; }

bool operator==(const Intersection &lhs, const Intersection &rhs) {
  return lhs.time() == rhs.time() && &lhs.object() == &rhs.object();
}

bool operator!=(const Intersection &lhs, const Intersection &rhs) {
  return !(lhs == rhs);
}

bool operator<(const Intersection &lhs, const Intersection &rhs) {
  return lhs.time() < rhs.time();
}
