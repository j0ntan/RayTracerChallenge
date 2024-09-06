#include <graphics/Color.hpp>
#include <utility/Float_compare.hpp>

Color::Color() : Tuple<3>{0, 0, 0} {}

Color::Color(double r, double g, double b) : Tuple<3>{r, g, b} {}

Color::Color(const Tuple<3> &values) : Tuple<3>(values) {}

double &Color::red() { return elements[0]; }

double &Color::green() { return elements[1]; }

double &Color::blue() { return elements[2]; }

double Color::red() const { return elements[0]; }

double Color::green() const { return elements[1]; }

double Color::blue() const { return elements[2]; }

Color operator+(const Color &lhs, const Color &rhs) {
  return Color(static_cast<Tuple<3>>(lhs) + static_cast<Tuple<3>>(rhs));
}

Color operator-(const Color &lhs, const Color &rhs) {
  return Color(static_cast<Tuple<3>>(lhs) - static_cast<Tuple<3>>(rhs));
}

Color operator*(const Color &lhs, const Color &rhs) {
  return Color(static_cast<Tuple<3>>(lhs) * static_cast<Tuple<3>>(rhs));
}

Color operator*(const Color &color, double scalar) {
  return Color(scalar * color.red(), scalar * color.green(),
               scalar * color.blue());
}

Color operator*(double scalar, const Color &color) { return color * scalar; }
