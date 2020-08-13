#include <math/Point.hpp>
#include <utility/Float_compare.hpp>

Point::Point(double x, double y, double z) : Tuple<3>{x, y, z} {};

Point::Point(const Tuple<3> &values) : Tuple<3>(values) {}

Point &Point::operator=(const Point &rhs) {
  elements = rhs.elements;
  return *this;
}
