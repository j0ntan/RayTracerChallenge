#include <algorithm>

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

std::optional<Intersection> hit(std::vector<Intersection> intersections) {
  std::sort(intersections.begin(), intersections.end());

  for (const auto &i : intersections)
    if (i.time() >= 0)
      return std::make_optional(i);

  return std::nullopt;
}
