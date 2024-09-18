#pragma once

#include <cstddef>
#include <string>

#include <graphics/Canvas.hpp>

/**
 * @brief Create the header string for the PPM file
 *
 * @param canvas Canvas object that contains size info needed
 * @return std::string Header string for PPM file
 */
std::string write_header(const Canvas &canvas);

/**
 * @brief
 *
 * @param color
 * @return std::string
 */
std::string to_string(const Color &color);

/**
 * @brief
 *
 * @param canvas
 * @return std::string
 */
std::string to_string(const Canvas &canvas);
