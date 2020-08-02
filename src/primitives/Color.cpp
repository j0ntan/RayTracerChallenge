#include <primitives/Color.hpp>
#include <utility/Float_compare.hpp>

Color::Color() : red{0}, green{0}, blue{0} {}

Color::Color(float r, float g, float b) : red{r}, green{g}, blue{b} {}

bool Color::operator==(const Color &rhs) const {
  if (this == &rhs)
    return true;

  return float_equals(red, rhs.red) && float_equals(green, rhs.green) &&
         float_equals(blue, rhs.blue);
}

Color Color::operator+(const Color &rhs) const {
  return Color(red + rhs.red, green + rhs.green, blue + rhs.blue);
}

Color Color::operator-(const Color &rhs) const {
  return Color(red - rhs.red, green - rhs.green, blue - rhs.blue);
}
