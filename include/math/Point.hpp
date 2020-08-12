#ifndef POINT_HPP
#define POINT_HPP

struct Point {
  Point();
  Point(double x, double y, double z);

  bool operator==(const Point &rhs) const;

  double x;
  double y;
  double z;
};

#endif
