#include <Math/Ray.hpp>

Point position(const Ray &ray, double t)
{
    return ray.origin + ray.direction * t;
}

Ray transform(const Ray &ray, const Matrix<4> &transformation)
{
    return Ray{Point(transformation * ray.origin),
               Vector(transformation * ray.direction)};
}
