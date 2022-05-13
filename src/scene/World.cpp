#include <scene/World.hpp>

std::vector<Sphere> World::objects() const { return objects_; }

std::vector<Light> World::light_sources() const { return light_sources_; }
