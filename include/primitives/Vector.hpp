#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
public:
  Vector();
  Vector(double x, double y, double z);

  bool operator==(const Vector &rhs) const;

  double x;
  double y;
  double z;
};

#endif
