#include <math/Intersection.hpp>

Intersection::Intersection(const double t, const Sphere &sphere)
    : t{t}, object{sphere} {}