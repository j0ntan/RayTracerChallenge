#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "Color.hpp"

/**
 * @brief Represents a digital canvas that holds the colors for our ray tracer
 * image
 *
 */
class Canvas {
public:
  /**
   * @brief Construct a new `Canvas` object
   *
   * @param width canvas width
   * @param height canvas height
   */
  Canvas(std::size_t width, std::size_t height);

  /**
   * @brief Access the pixel with the given `x` and `y` canvas coordinates
   *
   * @param x x-coordinate in range [0, width)
   * @param y y-coordinate in range [0, height)
   * @return Color The pixel color at the given xy-coordinates
   */
  Color pixel(std::size_t x, std::size_t y) const;

  /**
   * @brief Write a pixel value to the canvas
   *
   * @param x x-coordinate in range [0, width)
   * @param y y-coordinate in range [0, height)
   * @param color Color of the pixel value to be written
   */
  void write(std::size_t x, std::size_t y, const Color &color);

  /**
   * @brief Publicly accessible width & height of the canvas
   *
   */
  const std::size_t width, height;

private:
  /**
   * @brief 2D-array containing the pixel values that make up the canvas
   *
   */
  std::vector<std::vector<Color>> pixels;
};

void write_PPM(const Canvas &canvas, const std::string &filename);
