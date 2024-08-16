#include <math/Point.hpp>

Point::Point() : Tuple<4>{0, 0, 0, 1} {}

Point::Point(double x, double y, double z) : Tuple<4>{x, y, z, 1} {}

Point::Point(const Tuple<3> &values) : Point(values[0], values[1], values[2]) {}

Point::Point(const Tuple<4> &values) : Point(values[0], values[1], values[2]) {}

double &Point::x() { return elements[0]; }

double &Point::y() { return elements[1]; }

double &Point::z() { return elements[2]; }

double Point::x() const { return elements[0]; }

double Point::y() const { return elements[1]; }

double Point::z() const { return elements[2]; }
