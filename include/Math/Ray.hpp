#pragma once

#include <Math/Vector.hpp>
#include <Math/Matrix.hpp>

/**
 * @brief The ray objects used for ray tracing, consisting of an origin and a
 * direction
 *
 */
struct Ray
{
    Point origin;
    Vector direction;
};

/**
 * @brief Calculates the point obtained by traversing a distance 't' along the
 * ray's direction from the ray's origin
 *
 * @param ray The traversed ray
 * @param t The distance to traverse, in seconds
 * @return Point The point at distance 't' from the ray's origin
 */
Point position(const Ray &ray, double t);

/**
 * @brief Create a new ray by applying the given transformation to an input ray
 *
 * @param ray The ray to be transformed
 * @param transformation The 4x4 transformation matrix to apply
 * @return Ray The transformed ray
 */
Ray transform(const Ray &ray, const Matrix<4> &transformation);
