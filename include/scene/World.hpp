#ifndef WORLD_HPP
#define WORLD_HPP

#include <scene/Light.hpp>
#include <scene/Sphere.hpp>
#include <vector>

class World {
public:
  World() = default;

  std::vector<Sphere> objects() const;
  std::vector<Light> light_sources() const;

private:
  std::vector<Sphere> objects_;
  std::vector<Light> light_sources_;
};

#endif
