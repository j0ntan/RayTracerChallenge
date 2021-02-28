#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <cmath>
#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Ray.hpp>
#include <math/Vector.hpp>

const double PI = std::acos(-1);

Matrix<4> translate(double x, double y, double z);

Matrix<4> scale(double x, double y, double z);

Matrix<4> rotate_x(double theta);

Matrix<4> rotate_y(double theta);

Matrix<4> rotate_z(double theta);

Matrix<4> shear(double x_y, double x_z, double y_x, double y_z, double z_x,
                double z_y);

Ray transform(const Ray &ray, const Matrix<4> &m);

#endif
