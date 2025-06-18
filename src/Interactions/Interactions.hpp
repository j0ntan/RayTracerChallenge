#pragma once

#include <vector>
#include <optional>
#include <Math/Ray.hpp>
#include <Interactions/Intersection.hpp>
#include <World/World.hpp>
#include <World/Computations.hpp>

/**
 * @brief Sorts a set of intersections in ascending order
 *
 * @param intersections The set of intersections to sort
 * @return std::vector<Intersection> The sorted intersections
 */
std::vector<Intersection>
intersections(const std::vector<Intersection> &intersections);

/**
 * @brief Calculates the intersection of a ray and a shape
 *
 * @param sphere The shape to intersect with
 * @param ray The ray to intersect
 * @return std::vector<Intersection> The set of intersections, if any
 */
std::vector<Intersection> intersect(const Shape &shape, const Ray &ray);

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

/**
 * @brief Calculates the intersections of a ray with all objects in a world
 *
 * @param world The world containing objects to intersect
 * @param ray The ray that intersects with the world
 * @return std::vector<Intersection> The set of intersections found in the world
 */
std::vector<Intersection> intersect_world(const World &world, const Ray &ray);

/**
 * @brief Collects precomputed intersection data to reuse in further
 * calculations
 *
 * @param intersection An existing intersection
 * @param ray The ray that produced the intersection
 * @return Computations The precomputed values for the intersection
 */
Computations prepare_computations(const Intersection &intersection,
                                  const Ray &ray);

/**
 * @brief Returns the color at the intersection that produced the computations
 *
 * @param world The world containing intersected objects
 * @param computations The precomputed values for the intersection
 * @return Color The color shade for the hit
 */
Color shade_hit(const World &world, const Computations &computations);

/**
 * @brief Intersects a ray with the world and returns the color at the hit point
 *
 * @param world The world containing objects to intersect
 * @param ray The ray to intersect with the world
 * @return Color The color at the intersection point, or black if no hit occurs
 */
Color color_at(const World &world, const Ray &ray);

/**
 * @brief Checks if a point in the world is shadowed by any object
 *
 * @param world The world containing objects
 * @param point The point to check for shadowing
 * @return true if the point is shadowed by an object in the world
 * @return false if the point is not shadowed
 */
bool is_shadowed(const World &world, const Point &point);
