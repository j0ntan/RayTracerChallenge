#ifndef WORLD_HPP
#define WORLD_HPP

#include <scene/Intersection.hpp>
#include <scene/Light.hpp>
#include <scene/Sphere.hpp>
#include <vector>

class World {
public:
  World() = default;

  std::vector<Sphere> objects() const;
  std::vector<Light> light_sources() const;

  void add_sphere(const Sphere &s);
  void add_light_source(const Light &l);

private:
  std::vector<Sphere> objects_;
  std::vector<Light> light_sources_;
};

World default_world();
std::vector<Intersection> intersect_world(const World &world, const Ray &ray);

#endif
