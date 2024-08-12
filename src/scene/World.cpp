#include <algorithm>
#include <scene/Computations.hpp>
#include <scene/Intersections.hpp>
#include <scene/Lighting.hpp>
#include <scene/Transformations.hpp>
#include <scene/World.hpp>

std::vector<Sphere> World::objects() const { return objects_; }

std::vector<Light> World::light_sources() const { return light_sources_; }

void World::add_sphere(const Sphere &s) { objects_.push_back(s); }

void World::clear_spheres() { objects_.clear(); }

void World::add_light_source(const Light &l) { light_sources_.push_back(l); }

void World::clear_light_sources() { light_sources_.clear(); }

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

Color shade_hit(const World &world, const Computations &computations) {
  return lighting(computations.object->material(),
                  world.light_sources().front(), computations.point,
                  computations.eyev, computations.normalv);
}

Color color_at(const World &world, const Ray &ray) {
  auto intersections = intersect_world(world, ray);

  Color color{};
  if (!intersections.empty()) {
    auto hit_it = std::find_if(intersections.begin(), intersections.end(),
                               [](const Intersection &intersection) {
                                 return intersection.time() > 0;
                               });
    auto comps = prepare_computations(*hit_it, ray);
    color = shade_hit(world, comps);
  }

  return color;
}

bool is_shadowed(const World &world, const Point &point) {
  auto v = world.light_sources().front().position - point;
  auto distance = v.magnitude();
  auto direction = v.normalize();

  auto r = Ray(point, direction);
  auto intersections = intersect_world(world, r);

  auto h = hit(intersections);

  return h.has_value() && (h->time() < distance);
}
