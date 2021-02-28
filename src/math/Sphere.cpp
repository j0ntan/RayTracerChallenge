#include <math/Sphere.hpp>

Sphere::Sphere() : r{1.0}, origin_{Point(0, 0, 0)} {}

Sphere::Sphere(const double radius, const Point &origin)
    : r{radius}, origin_{origin} {}

double Sphere::radius() const { return r; }

Point Sphere::origin() const { return origin_; }

Matrix<4> Sphere::transformation() const { return identity; }
