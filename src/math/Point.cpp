#include <math/Point.hpp>
#include <utility/Float_compare.hpp>

Point::Point() : Tuple<3>{0, 0, 0} {}

Point::Point(double x, double y, double z) : Tuple<3>{x, y, z} {};

Point::Point(const Tuple<3> &values) : Tuple<3>(values) {}

Point &Point::operator=(const Point &rhs) {
  elements = rhs.elements;
  return *this;
}

double &Point::x() { return elements[0]; }

double &Point::y() { return elements[1]; }

double &Point::z() { return elements[2]; }

double Point::x() const { return elements[0]; }

double Point::y() const { return elements[1]; }

double Point::z() const { return elements[2]; }
