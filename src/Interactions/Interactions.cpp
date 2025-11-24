#include <cmath>
#include <algorithm>
#include <Interactions/Interactions.hpp>
#include <Interactions/Lighting.hpp>
#include <Float_compare.hpp>
#include <Math/Shape.hpp>

namespace
{
    bool operator==(const Intersection &lhs, const Intersection &rhs)
    {
        return float_equals(lhs.t, rhs.t) && lhs.object == rhs.object;
    }
}

std::vector<Intersection>
intersections(const std::vector<Intersection> &set)
{
    std::vector<Intersection> sorted(set);
    std::sort(sorted.begin(), sorted.end(),
              [=](auto i1, auto i2)
              { return i1.t < i2.t; });
    return sorted;
}

std::vector<Intersection> intersect(const Shape &shape, const Ray &ray)
{
    auto local_ray = transform(ray, inverse(shape.transform));
    return shape.local_intersect(local_ray);
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

Computations prepare_computations(
    const Intersection &intersection, const Ray &ray,
    std::vector<Intersection> all_intersections)
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
    comps.under_point = comps.point - comps.normalv * EPSILON;

    comps.reflectv = reflect(ray.direction, comps.normalv);

    comps.n1 = comps.n2 = 1.0;
    const auto &hit = intersection;
    std::vector<const Shape *> containers;
    if (all_intersections.empty())
    {
        all_intersections.push_back(intersection);
    }
    for (auto i : all_intersections)
    {
        if (i == hit)
        {
            if (containers.empty())
            {
                comps.n1 = 1.0;
            }
            else
            {
                comps.n1 = containers.back()->material.refractive_index;
            }
        }

        if (std::find(containers.cbegin(), containers.cend(), i.object) !=
            containers.cend())
        {
            std::erase(containers, i.object);
        }
        else
        {
            containers.push_back(i.object);
        }

        if (i == hit)
        {
            if (containers.empty())
            {
                comps.n2 = 1.0;
            }
            else
            {
                comps.n2 = containers.back()->material.refractive_index;
            }

            break;
        }
    }

    return comps;
}

Color shade_hit(const World &world, const Computations &comps, int remaining)
{
    auto shadowed = is_shadowed(world, comps.over_point);

    auto surface = lighting(*comps.object, *world.light, comps.over_point,
                            comps.eyev, comps.normalv, shadowed);

    auto reflected = reflected_color(world, comps, remaining);

    return surface + reflected;
}

Color color_at(const World &world, const Ray &ray, int remaining)
{
    Color color;

    auto intersections = intersect_world(world, ray);

    if (auto the_hit = hit(intersections))
    {
        auto sorted_intersections = ::intersections(intersections);
        auto computations = prepare_computations(*the_hit, ray,
                                                 sorted_intersections);
        color = shade_hit(world, computations, remaining);
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

Color reflected_color(const World &world, const Computations &computations,
                      int remaining)
{
    Color color;

    if (!float_equals(computations.object->material.reflective, 0) &&
        remaining > 0)
    {
        auto reflect_ray = Ray(computations.over_point, computations.reflectv);
        color = color_at(world, reflect_ray, remaining - 1);
        color = color * computations.object->material.reflective;
    }

    return color;
}

Color refracted_color(const World &world, const Computations &computations,
                      int remaining)
{
    const bool IS_OPAQUE =
        float_equals(computations.object->material.transparency, 0);
    const bool AT_MAX_DEPTH = remaining == 0;

    // check for total internal reflection
    auto n_ratio = computations.n1 / computations.n2;
    auto cos_i = dot(computations.eyev, computations.normalv);
    auto sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));
    const bool AT_TOTAL_INTERNAL_REFLECTION = sin2_t > 1.0;

    Color color(Color::BLACK);

    // Spawn the refracted ray and calculate the refracted color
    if (!IS_OPAQUE && !AT_MAX_DEPTH && !AT_TOTAL_INTERNAL_REFLECTION)
    {
        // Find cos_t via trig identity
        auto cos_t = std::sqrt(1.0 - sin2_t);
        // Compute the direction of the refracted ray
        auto direction = computations.normalv * (n_ratio * cos_i - cos_t) -
                         computations.eyev * n_ratio;
        // Create the refracted ray
        auto refract_ray = Ray(computations.under_point, direction);
        // Find the color of the refracted ray, making sure to multiply
        // by the transparency value to account for any opacity
        color = color_at(world, refract_ray, remaining - 1) *
                computations.object->material.transparency;
    }

    return color;
}
