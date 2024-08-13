#include <cmath>
#include <utility/Float_compare.hpp>

bool float_equals(const double number1, const double number2) {
  return std::abs(number2 - number1) <= EPSILON;
}
