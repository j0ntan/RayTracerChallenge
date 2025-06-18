#include <World/World.hpp>
#include <Math/Transformations.hpp>
#include <Math/Sphere.hpp>

World default_world()
{
    World world;

    world.light =
        std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

    world.objects.emplace_back(new Sphere);
    world.objects.front()->material.color = Color(0.8, 1.0, 0.6);
    world.objects.front()->material.diffuse = 0.7;
    world.objects.front()->material.specular = 0.2;

    world.objects.emplace_back(new Sphere);
    world.objects.back()->transform = scaling(0.5, 0.5, 0.5);

    return world;
}
