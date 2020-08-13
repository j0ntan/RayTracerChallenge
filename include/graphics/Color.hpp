#ifndef COLOR_HPP
#define COLOR_HPP

#include <math/Tuple.hpp>

struct Color final : public Tuple<3> {
  Color() = default;
  Color(double r, double g, double b);
  Color(const Tuple<3> &values);

  Color &operator=(const Color &rhs);

  double &red = elements[0];
  double &green = elements[1];
  double &blue = elements[2];
};

Color operator+(const Color &lhs, const Color &rhs);
Color operator-(const Color &lhs, const Color &rhs);
Color operator*(const Color &lhs, double rhs);
Color operator*(double lhs, const Color &rhs);
Color operator*(const Color &lhs, const Color &rhs);

#endif
