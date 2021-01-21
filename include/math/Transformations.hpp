#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <cmath>
#include <math/Matrix.hpp>
#include <math/Point.hpp>
#include <math/Vector.hpp>

const double PI = std::acos(-1);

Matrix<4> translate(double x, double y, double z);

Matrix<4> scale(double x, double y, double z);

Matrix<4> rotate_x(double theta);

Matrix<4> rotate_y(double theta);

Matrix<4> rotate_z(double theta);

#endif
