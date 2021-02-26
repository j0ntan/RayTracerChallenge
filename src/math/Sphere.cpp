#include <math/Sphere.hpp>

Sphere::Sphere() : r{1.0} {}

Sphere::Sphere(const double radius, const Point &origin) : r{radius} {}

double Sphere::radius() const { return r; }
