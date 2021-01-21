#include <cmath>
#include <math/Vector.hpp>
#include <utility/Float_compare.hpp>

Vector::Vector() : Tuple<4>{0, 0, 0, 0} {}

Vector::Vector(double x, double y, double z) : Tuple<4>{x, y, z, 0} {}

Vector::Vector(const Tuple<3> &values)
    : Tuple<4>{values.elements[0], values.elements[1], values.elements[2], 0} {}

Vector::Vector(const Tuple<4> &values)
    : Tuple<4>{values.elements[0], values.elements[1], values.elements[2], 0} {}

Vector &Vector::operator=(const Vector &rhs) {
  elements = rhs.elements;
  return *this;
}

double &Vector::x() { return elements[0]; }

double &Vector::y() { return elements[1]; }

double &Vector::z() { return elements[2]; }

double Vector::x() const { return elements[0]; }

double Vector::y() const { return elements[1]; }

double Vector::z() const { return elements[2]; }

double Vector::magnitude() const {
  return std::sqrt(inner_product(*this, *this));
}

Vector Vector::normalize() const { return *this / magnitude(); }

Point operator+(const Vector &lhs, const Point &rhs) {
  return Point(static_cast<Tuple<4>>(lhs) + static_cast<Tuple<4>>(rhs));
}

Point operator+(const Point &lhs, const Vector &rhs) { return rhs + lhs; }

Point operator-(const Point &lhs, const Vector &rhs) {
  return Point(static_cast<Tuple<4>>(lhs) - static_cast<Tuple<4>>(rhs));
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) + static_cast<Tuple<4>>(rhs));
}

Vector operator-(const Vector &vector) {
  return Vector(-(static_cast<Tuple<4>>(vector)));
}

Vector operator-(const Point &lhs, const Point &rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) - static_cast<Tuple<4>>(rhs));
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) - static_cast<Tuple<4>>(rhs));
}

Vector operator*(const Vector &lhs, double rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) * rhs);
}

Vector operator*(double lhs, const Vector &rhs) { return rhs * lhs; }

Vector operator/(const Vector &lhs, double rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) / rhs);
}

double dot(const Vector &lhs, const Vector &rhs) {
  return inner_product(lhs, rhs);
}

Vector cross(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                lhs.x() * rhs.y() - lhs.y() * rhs.x());
}
