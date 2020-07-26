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
