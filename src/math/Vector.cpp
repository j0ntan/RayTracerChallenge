#include <cmath>
#include <math/Vector.hpp>
#include <utility/Float_compare.hpp>

Vector::Vector(double x, double y, double z) : Tuple<3>{x, y, z} {}

Vector::Vector(const Tuple<3> &values) : Tuple<3>(values) {}

Vector &Vector::operator=(const Vector &rhs) {
  elements = rhs.elements;
  return *this;
}

double Vector::magnitude() const {
  return std::sqrt(inner_product(*this, *this));
}

Vector Vector::normalize() const { return *this / magnitude(); }

Point operator+(const Vector &lhs, const Point &rhs) {
  return Point(static_cast<Tuple<3>>(lhs) + static_cast<Tuple<3>>(rhs));
}

Point operator+(const Point &lhs, const Vector &rhs) { return rhs + lhs; }

Point operator-(const Point &lhs, const Vector &rhs) {
  return Point(static_cast<Tuple<3>>(lhs) - static_cast<Tuple<3>>(rhs));
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
  return Vector(static_cast<Tuple<3>>(lhs) + static_cast<Tuple<3>>(rhs));
}

Vector operator-(const Vector &vector) { return vector * -1.; }

Vector operator-(const Point &lhs, const Point &rhs) {
  return Vector(static_cast<Tuple<3>>(lhs) - static_cast<Tuple<3>>(rhs));
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
  return Vector(static_cast<Tuple<3>>(lhs) - static_cast<Tuple<3>>(rhs));
}

Vector operator*(const Vector &lhs, double rhs) {
  return Vector(static_cast<Tuple<3>>(lhs) * rhs);
}

Vector operator*(double lhs, const Vector &rhs) { return rhs * lhs; }

Vector operator/(const Vector &lhs, double rhs) {
  return Vector(static_cast<Tuple<3>>(lhs) / rhs);
}

double dot(const Vector &lhs, const Vector &rhs) {
  return inner_product(lhs, rhs);
}

Vector cross(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x);
}
