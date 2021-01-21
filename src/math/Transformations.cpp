#include <math/Matrix.hpp>
#include <math/Transformations.hpp>

Matrix<4> translate(double x, double y, double z) {
  Matrix<4> translation = identity;
  translation(0, 3) = x;
  translation(1, 3) = y;
  translation(2, 3) = z;
  return translation;
}

Matrix<4> scale(double x, double y, double z) {
  Matrix<4> scaling = identity;
  scaling(0, 0) = x;
  scaling(1, 1) = y;
  scaling(2, 2) = z;
  return scaling;
}
