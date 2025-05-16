#pragma once

#include <string>
#include <vector>
#include <Graphics/Color.hpp>

namespace PPM
{
    /**
     * @brief The max allowed value for a color's RGB components
     *
     */
    constexpr std::size_t MAX_COLOR_VALUE = 255;

    /**
     * @brief Write a PPM-formatted header string
     *
     * @param width The canvas width
     * @param height The canvas height
     * @return std::string The formatted header string
     */
    std::string write_header(std::size_t width, std::size_t height);

    /**
     * @brief Convert a set of colors to a PPM-formatted string
     *
     * The color values are scaled to an integer in the range [0,255]. The
     * canvas width determines how many colors fit on a single line. Any lines
     * that exceed a 70-character limit are split into multiple lines. The last
     * line of the string is always terminated with a newline character.
     *
     * @param data The image data as a set of colors
     * @param canvas_width The width of the canvas
     * @return std::string The PPM-formatted image data
     */
    std::string write_data(
        const std::vector<Color> &data, const std::size_t &canvas_width);

    /**
     * @brief Convert a color object to a formatted string representation
     *
     * The color object is assumed to have unbounded floating-point RGB values.
     * Each component gets bounded to the range [0,255] and rounded to the
     * nearest integer. A single space separates adjacent components.
     *
     * @param color The color whose RBG values will be converted
     * @return std::string The formatted string conversion
     */
    std::string to_string(const Color &color);

    /**
     * @brief Split a long string into multiple length-limited lines
     *
     * The string is assumed to contain many space-separated values and one or
     * more newline characters. The string is split, if needed, by converting
     * space characters into newlines so that no line exceeds the specified
     * limit.
     *
     * @param lines_str The string to be split in-place
     * @param limit The max allowed length for any line
     */
    void split_line(std::string &lines_str, const std::size_t limit);
}
