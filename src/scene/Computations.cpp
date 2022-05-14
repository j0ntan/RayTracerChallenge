#include <scene/Computations.hpp>

Computations prepare_computations(const Intersection &intersection,
                                  const Ray &ray) {
  Computations comps;
  comps.t = intersection.time();
  comps.object = &intersection.object();

  comps.point = position(ray, comps.t);
  comps.eyev = -ray.direction;
  comps.normalv = comps.object->normal(comps.point);

  return comps;
}
