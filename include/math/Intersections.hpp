#ifndef INTERSECTIONS_HPP
#define INTERSECTIONS_HPP

#include <math/Ray.hpp>
#include <math/Sphere.hpp>
#include <vector>

std::vector<double> intersect(const Sphere &sphere, const Ray &ray);

#endif
