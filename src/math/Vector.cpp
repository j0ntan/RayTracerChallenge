#include <math/Vector.hpp>

Vector::Vector(double x, double y, double z) : Tuple<4>{x, y, z, 0} {}

Vector::Vector(const Tuple<3> &values)
    : Vector{values[0], values[1], values[2]} {}

Vector::Vector(const Tuple<4> &values)
    : Vector{values[0], values[1], values[2]} {}

double Vector::magnitude() const {
  return std::sqrt(inner_product(*this, *this));
}

Vector Vector::normalize() const { return *this / magnitude(); }

double &Vector::x() { return elements[0]; }

double &Vector::y() { return elements[1]; }

double &Vector::z() { return elements[2]; }

double Vector::x() const { return elements[0]; }

double Vector::y() const { return elements[1]; }

double Vector::z() const { return elements[2]; }

Point operator+(const Vector &displacement, const Point &point) {
  return Point(static_cast<Tuple<4>>(displacement) +
               static_cast<Tuple<4>>(point));
}

Point operator+(const Point &point, const Vector &displacement) {
  return displacement + point;
}

Point operator-(const Point &point, const Vector &displacement) {
  return Point(static_cast<Tuple<4>>(point) -
               static_cast<Tuple<4>>(displacement));
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) + static_cast<Tuple<4>>(rhs));
}

Vector operator-(const Vector &vector) {
  return Vector(-(static_cast<Tuple<4>>(vector)));
}

Vector operator-(const Point &p1, const Point &p2) {
  return Vector(static_cast<Tuple<4>>(p1) - static_cast<Tuple<4>>(p2));
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
  return Vector(static_cast<Tuple<4>>(lhs) - static_cast<Tuple<4>>(rhs));
}

Vector operator*(const Vector &vector, double scalar) {
  return Vector(static_cast<Tuple<4>>(vector) * scalar);
}

Vector operator*(double scalar, const Vector &vector) {
  return vector * scalar;
}

Vector operator/(const Vector &vector, double scalar) {
  return Vector(static_cast<Tuple<4>>(vector) / scalar);
}

double dot(const Vector &lhs, const Vector &rhs) {
  return inner_product(lhs, rhs);
}

Vector cross(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

Vector reflect(const Vector &incident, const Vector &normal) {
  return Vector(incident - normal * 2 * dot(incident, normal));
}
