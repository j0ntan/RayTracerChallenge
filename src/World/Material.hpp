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
    /**
     * @brief The base color of the material
     *
     */
    Color color = {1, 1, 1};

    /**
     * @brief Coefficient of ambient reflection, typically between 0 and 1
     *
     * This component models the ambient background lighting contributed by
     * reflections from other objects in the environment. The Phong model
     * treats this as a constant, coloring all points on the surface equally.
     *
     */
    double ambient = {0.1};

    /**
     * @brief Coefficient of diffuse reflection, typically between 0 and 1
     *
     * This component models the diffuse light reflected from a matte surface.
     * Diffuse reflection arises from the assumption that light from any
     * direction is reflected uniformly in all directions. It depends only on
     * the angle between the light source and the surface normal.
     *
     */
    double diffuse = {0.9};

    /**
     * @brief Coefficient of specular reflection, typically between 0 and 1
     *
     * This component models the reflection of the light source itself and
     * results in specular highlight, or a bright spot on a curved surface. It
     * depends only on the angle between the reflection vector and the eye
     * vector.
     *
     */
    double specular = {0.9};

    /**
     * @brief A constant measuring the shininess of a material
     *
     * It is larger for surfaces that are smoother and more mirror-like,
     * producing a small specular highlight. Values range between 10 (very
     * large highlight) and 200 (very small highlight), though there is no
     * actual upper bound.
     *
     */
    double shininess = {200};

    /**
     * @brief An optional pattern for the material's surface
     *
     * The pointer is NULL when there is not pattern applied, or it points to
     * the pattern set for this material.
     *
     */
    std::unique_ptr<Pattern> pattern;

    /**
     * @brief Coefficient of a material's reflectiveness
     *
     * A value of 0 indicates the surface is completely nonreflective, whereas
     * a value of 1 indicates a perfect mirror-like surface.
     *
     */
    double reflective = {0.0};

    /**
     * @brief Coefficient of transparency
     *
     * A value of 0 indicates the surface is completely nontransparent, whereas
     * a value of 1 indicates a fully transparent surface.
     *
     */
    double transparency = {0.0};

    /**
     * @brief The refractive index coefficient for the material's parent object
     *
     */
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
