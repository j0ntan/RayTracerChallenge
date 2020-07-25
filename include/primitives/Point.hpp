#ifndef POINT_HPP
#define POINT_HPP

struct Point {
  Point() : x{0}, y{0}, z{0} {}
  Point(double x, double y, double z) : x{x}, y{y}, z{z} {};

  const double x;
  const double y;
  const double z;
};

#endif
