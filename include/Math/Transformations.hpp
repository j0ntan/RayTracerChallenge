#pragma once

#include <Math/Matrix.hpp>

/**
 * @brief Create a translation matrix
 *
 * @param x Displacement in the x-component
 * @param y Displacement in the y-component
 * @param z Displacement in the z-component
 * @return Matrix<4> Translation matrix
 */
Matrix<4> translation(double x, double y, double z);

/**
 * @brief Create a scaling matrix
 *
 * @param x Scale factor for the x-component
 * @param y Scale factor for the y-component
 * @param z Scale factor for the z-component
 * @return Matrix<4> Scaling matrix
 */
Matrix<4> scaling(double x, double y, double z);

/**
 * @brief Create a rotation matrix about the x-axis
 *
 * @param theta Angle of rotation (rad)
 * @return Matrix<4> Rotation matrix about the x-axis
 */
Matrix<4> rotation_x(double theta);

/**
 * @brief Create a rotation matrix about the y-axis
 *
 * @param theta Angle of rotation (rad)
 * @return Matrix<4> Rotation matrix about the y-axis
 */
Matrix<4> rotation_y(double theta);

/**
 * @brief Create a rotation matrix about the z-axis
 *
 * @param theta Angle of rotation (rad)
 * @return Matrix<4> Rotation matrix about the z-axis
 */
Matrix<4> rotation_z(double theta);

/**
 * @brief Create a shear, or skew, matrix
 *
 * When applied to a tuple, a shearing transformation changes each component of
 * the tuple in proportion to the other two components.
 *
 * @param x_y Change x in proportion to y
 * @param x_z Change x in proportion to z
 * @param y_x Change y in proportion to x
 * @param y_z Change y in proportion to z
 * @param z_x Change z in proportion to x
 * @param z_y Change z in proportion to y
 * @return Matrix<4> Shearing matrix
 */
Matrix<4> shearing(
    double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);
