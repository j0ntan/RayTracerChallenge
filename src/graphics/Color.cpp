#include <graphics/Color.hpp>
#include <utility/Float_compare.hpp>

Color::Color() : Tuple<3>{0, 0, 0} {}

Color::Color(double r, double g, double b) : Tuple<3>{r, g, b} {}

Color::Color(const Tuple<3> &values) : Tuple<3>(values) {}

Color &Color::operator=(const Color &rhs) {
  elements = rhs.elements;
  return *this;
}

Color operator+(const Color &lhs, const Color &rhs) {
  return Color(static_cast<Tuple<3>>(lhs) + static_cast<Tuple<3>>(rhs));
}

Color operator-(const Color &lhs, const Color &rhs) {
  return Color(static_cast<Tuple<3>>(lhs) - static_cast<Tuple<3>>(rhs));
}

Color operator*(const Color &lhs, const Color &rhs) {
  return Color(static_cast<Tuple<3>>(lhs) * static_cast<Tuple<3>>(rhs));
}

Color operator*(const Color &lhs, double rhs) {
  return Color(rhs * lhs.red, 2 * lhs.green, 2 * lhs.blue);
}

Color operator*(double lhs, const Color &rhs) { return rhs * lhs; }
