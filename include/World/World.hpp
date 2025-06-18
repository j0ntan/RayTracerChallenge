#pragma once

#include <vector>
#include <memory>
#include <Math/Shape.hpp>
#include <World/PointLight.hpp>

/**
 * @brief The ray tracer world containing objects and light sources
 *
 */
struct World
{
    std::vector<std::shared_ptr<Shape>> objects;
    std::shared_ptr<PointLight> light = nullptr;
};

World default_world();
