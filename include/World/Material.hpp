#pragma once

#include <optional>
#include <Graphics/Color.hpp>
#include <Graphics/StripePattern.hpp>

/**
 * @brief Defines the reflective properties for world objects
 *
 * @note These properties are used in the reflective light calculation
 *  according to the Phong reflection model.
 *
 */
struct Material
{
    Color color = {1, 1, 1};
    double ambient = {0.1};
    double diffuse = {0.9};
    double specular = {0.9};
    double shininess = {200};
    std::optional<StripePattern> pattern;
};
