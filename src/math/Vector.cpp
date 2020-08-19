#include <cmath>
#include <math/Vector.hpp>
#include <utility/Float_compare.hpp>

Vector::Vector() : x{0}, y{0}, z{0} {}

Vector::Vector(double x, double y, double z) : x{x}, y{y}, z{z} {}

bool Vector::operator==(const Vector &rhs) const {
  if (&rhs == this)
    return true;

  return float_equals(x, rhs.x) && float_equals(y, rhs.y) &&
         float_equals(z, rhs.z);
}

double Vector::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

Vector Vector::normalize() const {
  const auto R = magnitude();
  return Vector(x / R, y / R, z / R);
}

Point operator+(const Vector &lhs, const Point &rhs) {
  return Point(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Point operator+(const Point &lhs, const Vector &rhs) { return rhs + lhs; }

Point operator-(const Point &lhs, const Vector &rhs) {
  return Point(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector operator-(const Vector &vector) { return -1 * vector; }

Vector operator-(const Point &lhs, const Point &rhs) {
  return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector operator*(const Vector &lhs, double rhs) {
  return Vector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector operator*(double lhs, const Vector &rhs) { return rhs * lhs; }

Vector operator/(const Vector &lhs, double rhs) {
  return Vector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

double dot(const Vector &lhs, const Vector &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector cross(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x);
}
