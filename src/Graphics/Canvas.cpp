#include <cmath>
#include <fstream>
#include <PPM.hpp>
#include <Graphics/Canvas.hpp>

namespace
{
    /**
     * @brief The max allowed value for a color's RGB components
     *
     */
    constexpr std::size_t MAX_COLOR_VALUE = 255;

    /**
     * @brief Scale a floating-point value to an integer in the range [0,255]
     *
     * @param x The floating-point value to be scaled
     * @return int The scaled integer value
     */
    int scale(double x)
    {
        return std::round(x * MAX_COLOR_VALUE);
    }

    /**
     * @brief Clamp a floating-point value to the range [0,1]
     *
     * @param x The floating-point value to be clamped
     * @return double The clamped value
     */
    double clamp(double x)
    {
        constexpr double CLAMP_MIN = 0.0, CLAMP_MAX = 1.0;
        return std::max(CLAMP_MIN, std::min(CLAMP_MAX, x));
    }

    /**
     * @brief Convert a color object to a formatted string representation
     *
     * @param color The color whose RBG values will be converted
     * @return std::string The formatted string conversion
     */
    std::string to_string(const Color &color)
    {
        return std::to_string(scale(clamp(color.red()))) + ' ' +
               std::to_string(scale(clamp(color.green()))) + ' ' +
               std::to_string(scale(clamp(color.blue())));
    }
}

Canvas::Canvas(std::size_t width, std::size_t height)
    : WIDTH{width}, HEIGHT{height},
      pixels{std::vector<std::vector<Color>>(
          HEIGHT, std::vector<Color>(WIDTH, Color{0, 0, 0}))}
{
}

void Canvas::write_pixel(std::size_t x, std::size_t y, const Color &color)
{
    pixels[y][x] = color;
}

Color Canvas::pixel_at(std::size_t x, std::size_t y) const
{
    return pixels[y][x];
}

std::string Canvas::write_ppm() const
{
    std::vector<Color> data;
    for (const auto &row : pixels)
    {
        data.insert(data.end(), row.begin(), row.end());
    }

    return PPM::write_header(WIDTH, HEIGHT) + PPM::write_data(data, WIDTH);
}

void Canvas::fill_pixels(const Color &color)
{
    for (std::size_t row = 0; row < HEIGHT; ++row)
    {
        for (std::size_t col = 0; col < WIDTH; ++col)
        {
            write_pixel(col, row, color);
        }
    }
}

void write_PPM_file(const Canvas &canvas, std::string filename)
{
    std::ofstream out_file(filename + ".ppm");
    auto data = canvas.write_ppm();
    out_file << data;
}
