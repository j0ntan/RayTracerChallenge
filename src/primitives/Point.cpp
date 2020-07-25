#include <primitives/Point.hpp>
#include <utility/Float_compare.hpp>

Point::Point() : x{0}, y{0}, z{0} {}

Point::Point(double x, double y, double z) : x{x}, y{y}, z{z} {};

bool Point::operator==(const Point &rhs) const {
  if (&rhs == this)
    return true;

  return float_equals(x, rhs.x) && float_equals(y, rhs.y) &&
         float_equals(z, rhs.z);
}
