#include <cmath>
#include <algorithm>
#include <Interactions.hpp>
#include <Lighting.hpp>
#include <Float_compare.hpp>

std::vector<Intersection>
intersections(const std::vector<Intersection> &set)
{
    std::vector<Intersection> sorted(set);
    std::sort(sorted.begin(), sorted.end(),
              [=](auto i1, auto i2)
              { return i1.t < i2.t; });
    return sorted;
}

std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray)
{
    auto local_ray = transform(ray, inverse(sphere.transform));
    return sphere.local_intersect(local_ray);
}

std::optional<Intersection> hit(const std::vector<Intersection> &intersections)
{
    auto positive_hit_it =
        std::find_if(intersections.cbegin(), intersections.cend(),
                     [&](auto intersection)
                     { return intersection.t > 0; });

    return (positive_hit_it == intersections.end())
               ? std::nullopt
               : std::make_optional(*positive_hit_it);
}

std::vector<Intersection> intersect_world(const World &world, const Ray &ray)
{
    std::vector<Intersection> all_intersections;
    for (const auto &OBJECT : world.objects)
    {
        auto intersections = intersect(*OBJECT, ray);
        all_intersections.insert(all_intersections.end(),
                                 intersections.cbegin(), intersections.cend());
    }

    return intersections(all_intersections);
}

Computations prepare_computations(const Intersection &intersection,
                                  const Ray &ray)
{
    // instantiate a data structure for storing some precomputed values
    auto comps = Computations();

    // copy the intersection's properties, for convenience
    comps.t = intersection.t;
    comps.object = intersection.object;

    // precompute some useful values
    comps.point = position(ray, comps.t);
    comps.eyev = -ray.direction;
    comps.normalv = comps.object->normal_at(comps.point);

    if (dot(comps.normalv, comps.eyev) < 0)
    {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    }
    else
    {
        comps.inside = false;
    }

    comps.over_point = comps.point + comps.normalv * EPSILON;

    return comps;
}

Color shade_hit(const World &world, const Computations &comps)
{
    auto shadowed = is_shadowed(world, comps.over_point);

    return lighting(comps.object->material, *world.light, comps.over_point,
                    comps.eyev, comps.normalv, shadowed);
}

Color color_at(const World &world, const Ray &ray)
{
    Color color;

    auto intersections = intersect_world(world, ray);

    if (auto the_hit = hit(intersections))
    {
        auto computations = prepare_computations(*the_hit, ray);
        color = shade_hit(world, computations);
    }
    else
    {
        // return black
    }

    return color;
}

bool is_shadowed(const World &world, const Point &point)
{
    auto v = world.light->position - point;
    auto distance = magnitude(v);
    auto direction = normalize(v);

    auto r = Ray(point, direction);
    auto intersections = intersect_world(world, r);

    auto h = hit(intersections);

    return h && h->t < distance;
}
