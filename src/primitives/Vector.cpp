#include <primitives/Vector.hpp>
#include <utility/Float_compare.hpp>

Vector::Vector() : x{0}, y{0}, z{0} {}

Vector::Vector(double x, double y, double z) : x{x}, y{y}, z{z} {}

bool Vector::operator==(const Vector &rhs) const {
  if (&rhs == this)
    return true;

  return float_equals(x, rhs.x) && float_equals(y, rhs.y) &&
         float_equals(z, rhs.z);
}

Vector Vector::operator+(const Vector &rhs) const {
  return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Point Vector::operator+(const Point &rhs) const {
  return Point(x + rhs.x, y + rhs.y, z + rhs.z);
}

Point operator+(const Point &lhs, const Vector &rhs) { return rhs + lhs; }

Vector operator-(const Point &lhs, const Point &rhs) {
  return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Point operator-(const Point &lhs, const Vector &rhs) {
  return Point(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
