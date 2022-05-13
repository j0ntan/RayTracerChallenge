#include <algorithm>
#include <scene/Intersections.hpp>
#include <scene/Transformations.hpp>
#include <scene/World.hpp>

std::vector<Sphere> World::objects() const { return objects_; }

std::vector<Light> World::light_sources() const { return light_sources_; }

void World::add_sphere(const Sphere &s) { objects_.push_back(s); }

void World::add_light_source(const Light &l) { light_sources_.push_back(l); }

World default_world() {
  World w;
  Material m;
  m.color = Color{.8, 1, .6};
  m.diffuse = .7;
  m.specular = .2;
  Sphere s1, s2;
  s1.set_material(m);
  s2.set_transformation(scale(.5, .5, .5));
  w.add_sphere(s2);
  w.add_sphere(s1);
  w.add_light_source(Light{Point{-10, 10, -10}, Color{1, 1, 1}});
  return w;
}

std::vector<Intersection> intersect_world(const World &world, const Ray &ray) {
  std::vector<Intersection> intersections;

  const auto OBJECTS = world.objects();
  for (const auto &object : OBJECTS) {
    auto obj_intersections = intersect(object, ray);
    intersections.insert(intersections.end(), obj_intersections.begin(),
                         obj_intersections.end());
  }

  std::sort(intersections.begin(), intersections.end(),
            [](Intersection lhs, Intersection rhs) {
              return lhs.time() < rhs.time();
            });
  return intersections;
}
