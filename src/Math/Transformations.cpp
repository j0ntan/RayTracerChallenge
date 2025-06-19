#include <cmath>
#include <Math/Transformations.hpp>

// template <std::size_t N>
Matrix<4> translation(double x, double y, double z)
{
    return Matrix<4>({1, 0, 0, x,
                      0, 1, 0, y,
                      0, 0, 1, z,
                      0, 0, 0, 1});
}

Matrix<4> scaling(double x, double y, double z)
{
    return Matrix<4>({x, 0, 0, 0,
                      0, y, 0, 0,
                      0, 0, z, 0,
                      0, 0, 0, 1});
}

Matrix<4> rotation_x(double r)
{
    return Matrix<4>({1, 0, 0, 0,
                      0, std::cos(r), -std::sin(r), 0,
                      0, std::sin(r), std::cos(r), 0,
                      0, 0, 0, 1});
}

Matrix<4> rotation_y(double r)
{
    return Matrix<4>({std::cos(r), 0, std::sin(r), 0,
                      0, 1, 0, 0,
                      -std::sin(r), 0, std::cos(r), 0,
                      0, 0, 0, 1});
}

Matrix<4> rotation_z(double r)
{
    return Matrix<4>({std::cos(r), -std::sin(r), 0, 0,
                      std::sin(r), std::cos(r), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1});
}

Matrix<4> shearing(
    double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
    return Matrix<4>({1, x_y, x_z, 0,
                      y_x, 1, y_z, 0,
                      z_x, z_y, 1, 0,
                      0, 0, 0, 1});
}
