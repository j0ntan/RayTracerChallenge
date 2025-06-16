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

Matrix<4> view_transform(const Point &from, const Point &to, const Vector &up)
{
    auto forward = normalize(to - from);

    auto left = cross(forward, normalize(up));

    auto true_up = cross(left, forward);

    Matrix<4> orientation(
        {left.x(), left.y(), left.z(), 0,
         true_up.x(), true_up.y(), true_up.z(), 0,
         -forward.x(), -forward.y(), -forward.z(), 0,
         0, 0, 0, 1});

    auto neg_from = -from;
    return orientation *
           translation(-from.x(), -from.y(), -from.z());
}
