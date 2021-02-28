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

Matrix<4> rotate_x(double theta) {
  return Matrix<4>{{1, 0, 0, 0},
                   {0, cos(theta), -1 * sin(theta), 0},
                   {0, sin(theta), cos(theta), 0},
                   {0, 0, 0, 1}};
}

Matrix<4> rotate_y(double theta) {
  return Matrix<4>{{cos(theta), 0, sin(theta), 0},
                   {0, 1, 0, 0},
                   {-1 * sin(theta), 0, cos(theta), 0},
                   {0, 0, 0, 1}};
}

Matrix<4> rotate_z(double theta) {
  return Matrix<4>{{cos(theta), -1 * sin(theta), 0, 0},
                   {sin(theta), cos(theta), 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}};
}

Matrix<4> shear(double x_y, double x_z, double y_x, double y_z, double z_x,
                double z_y) {
  return Matrix<4>{
      {1, x_y, x_z, 0}, {y_x, 1, y_z, 0}, {z_x, z_y, 1, 0}, {0, 0, 0, 1}};
}

Ray transform(const Ray &ray, const Matrix<4> &m) { return ray; }
