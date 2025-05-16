#pragma once

#include <vector>
#include <string>
#include <Graphics/Color.hpp>

/**
 * @brief Represents a digital canvas that holds the colors for our ray tracer
 * image
 *
 */
class Canvas
{
public:
    /**
     * @brief Construct a canvas object with a given width and height
     *
     */
    Canvas(std::size_t width, std::size_t height);

    /**
     * @brief Write a pixel value to the canvas
     *
     * @param x x-coordinate in range [0, width)
     * @param y y-coordinate in range [0, height)
     * @param color Color to be written
     */
    void write_pixel(std::size_t x, std::size_t y, const Color &color);

    /**
     * @brief Access the pixel with the given x and y canvas coordinates
     *
     * @param x x-coordinate in range [0, width)
     * @param y y-coordinate in range [0, height)
     * @return Color The color at the given coordinates
     */
    Color pixel_at(std::size_t x, std::size_t y) const;

    /**
     * @brief Write the canvas to a PPM-formatted string
     *
     * @return std::string The PPM-formatted string
     */
    std::string write_ppm() const;

    /**
     * @brief Fill the entire canvas with a given color
     *
     * @param color Color to be used for filling
     */
    void fill_pixels(const Color &color);

    ////////////////////////
    /// Member Variables ///
    ////////////////////////

    /**
     * @brief Width & height of the canvas
     *
     */
    const std::size_t WIDTH;
    const std::size_t HEIGHT;

private:
    /**
     * @brief 2D vector of pixel colors
     *
     */
    std::vector<std::vector<Color>> pixels;
};

/**
 * @brief Write a PPM file to disk
 *
 * @param canvas The canvas to be written
 * @param filename The name of the file to be created
 */
void write_PPM_file(const Canvas &canvas, std::string filename);
