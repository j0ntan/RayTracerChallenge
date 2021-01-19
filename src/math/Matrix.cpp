#include <math/Matrix.hpp>

double determinant(const Matrix<2> &matrix) {
  return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
}
