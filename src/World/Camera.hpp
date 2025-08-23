#pragma once

#include <cstddef>
#include <Math/Ray.hpp>
#include <Graphics/Canvas.hpp>
#include <World/World.hpp>

/**
 * @brief A virtual camera for rendering scenes in a ray tracer
 *
 */
struct Camera
{
    /**
     * @brief Construct a new Camera object
     *
     * @param hsize horizontal size of the canvas
     * @param vsize vertical size of the canvas
     * @param field_of_view the field of view in radians
     */
    Camera(std::size_t hsize, std::size_t vsize, double field_of_view);

    ////////////////////////
    /// Member Variables ///
    ////////////////////////

    /**
     * @brief Horizontal size of the canvas
     *
     */
    std::size_t hsize;

    /**
     * @brief Vertical size of the canvas
     *
     */
    std::size_t vsize;

    /**
     * @brief Field of view in radians
     *
     */
    double field_of_view;

    /**
     * @brief Transformation matrix for the camera
     *
     */
    Matrix<4> transform = IDENTITY;

    /**
     * @brief The size of each pixel in world units
     *
     */
    double pixel_size;

    /**
     * @brief Half the width/height of the canvas in world units
     *
     */
    double half_width;
    double half_height;
};

/**
 * @brief Creates the ray pointing from the camera to a pixel on the canvas
 *
 * @param camera The camera used to render the scene
 * @param xpixel The canvas pixel's x-coordinate
 * @param ypixel The canvas pixel's y-coordinate
 * @return Ray The ray pointing from the camera to the pixel
 */
Ray ray_for_pixel(const Camera &camera, std::size_t xpixel, std::size_t ypixel);

/**
 * @brief Renders a scene from the perspective of a camera
 *
 * @param camera The camera used to render the scene
 * @param world The world containing objects to render
 * @return Canvas The rendered canvas containing the scene
 */
Canvas render(const Camera &camera, const World &world);
