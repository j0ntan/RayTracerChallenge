#pragma once

#include <vector>
#include <optional>
#include <Math/Ray.hpp>
#include <Intersection.hpp>

/**
 * @brief Sorts a set of intersections in ascending order
 *
 * @param intersections The set of intersections to sort
 * @return std::vector<Intersection> The sorted intersections
 */
std::vector<Intersection>
intersections(const std::vector<Intersection> &intersections);

/**
 * @brief Calculates the intersection of a ray and a sphere
 *
 * @param sphere The sphere to intersect with
 * @param ray The ray to intersect
 * @return std::vector<Intersection> The set of intersections, if any
 */
std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray);

/**
 * @brief Finds & returns the 'hit' from a set of intersections
 *
 * The 'hit' is the first intersection with a positive time value. If no hit is
 * found, std::nullopt is returned to indicate that there was no intersection.
 *
 * @param intersections The set of intersections to search
 * @return std::optional<Intersection> The optional intersection found to be the
 * 'hit
 */
std::optional<Intersection> hit(const std::vector<Intersection> &intersections);
