#include <cmath>
#include <numeric>
#include <stdexcept>
#include <Float_compare.hpp>
#include <Math/Vector.hpp>

Vector::Vector(double x, double y, double z) : Tuple{x, y, z, 0.0}
{
}

Vector::Vector(const Tuple &tuple) : Tuple{tuple}
{
    if (!float_equals(tuple.w(), 0.0))
        throw std::invalid_argument("Vector invalid with Tuple::w not 0.0");
}

Vector operator-(const Point &p1, const Point &p2)
{
    return Vector(static_cast<Tuple>(p1) - static_cast<Tuple>(p2));
}

bool operator==(const Vector &lhs, const Vector &rhs)
{
    return static_cast<Tuple>(lhs) == static_cast<Tuple>(rhs);
}

Point operator-(const Point &point, const Vector &displacement)
{
    return Point(static_cast<Tuple>(point) - static_cast<Tuple>(displacement));
}

Vector operator-(const Vector &lhs, const Vector &rhs)
{
    return Vector(static_cast<Tuple>(lhs) - static_cast<Tuple>(rhs));
}

Vector operator*(const Vector &vector, double scalar)
{
    return Vector(static_cast<Tuple>(vector) * scalar);
}

Vector operator*(double scalar, const Vector &vector)
{
    return vector * scalar;
}

double magnitude(const Vector &vector)
{
    return std::sqrt(dot(vector, vector));
}

Vector normalize(const Vector &vector)
{
    return vector / magnitude(vector);
}

double dot(const Vector &lhs, const Vector &rhs)
{
    return dot(static_cast<Tuple>(lhs), static_cast<Tuple>(rhs));
}

Vector cross(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                  lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                  lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

Vector reflect(const Vector &incident, const Vector &normal)
{
    return incident - normal * 2 * dot(incident, normal);
}
