#pragma once

#include <memory>
#include <Graphics/Color.hpp>
#include <Graphics/Pattern.hpp>

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
    std::unique_ptr<Pattern> pattern;
    double reflective = {0.0};
    double transparency = {0.0};
    double refractive_index = {1.0};

    /**
     * @brief Default construct a new Material object
     *
     */
    Material() = default;

    /**
     * @brief Copy construct a new Material object
     *
     * @param material The material to copy from
     */
    Material(const Material &material);

    /**
     * @brief Move construct a new Material object
     *
     * @param material The material to move from
     */
    Material(Material &&material) = default;

    /**
     * @brief Copy assignment operator
     *
     * @param rhs The right-hand side material
     * @return Material& The assigned material
     */
    Material &operator=(const Material &rhs);

    /**
     * @brief Move assignment operator
     *
     * @param rhs The right-hand side material
     * @return Material& The assigned material
     */
    Material &operator=(Material &&rhs) = default;
};
