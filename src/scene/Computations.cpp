#include <scene/Computations.hpp>
#include <utility/Float_compare.hpp>

Computations prepare_computations(const Intersection &intersection,
                                  const Ray &ray) {
  Computations comps;
  comps.t = intersection.time();
  comps.object = &intersection.object();

  comps.point = position(ray, comps.t);
  comps.eyev = -ray.direction;

  comps.normalv = comps.object->normal(comps.point);
  if (dot(comps.normalv, comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else
    comps.inside = false;

  comps.over_point = comps.point + comps.normalv * EPSILON;

  return comps;
}
