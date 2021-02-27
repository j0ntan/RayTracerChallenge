#ifndef INTERSECTIONS_HPP
#define INTERSECTIONS_HPP

#include "Intersection.hpp"
#include <math/Ray.hpp>
#include <math/Sphere.hpp>
#include <vector>

std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray);

Intersection hit(const std::vector<Intersection> &intersections);

#endif
