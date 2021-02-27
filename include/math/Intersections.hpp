#ifndef INTERSECTIONS_HPP
#define INTERSECTIONS_HPP

#include "Intersection.hpp"
#include <math/Ray.hpp>
#include <math/Sphere.hpp>
#include <optional>
#include <vector>

std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray);

std::optional<Intersection> hit(std::vector<Intersection> intersections);

#endif
