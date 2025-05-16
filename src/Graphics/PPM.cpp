#include <cmath>
#include <string_view>
#include <PPM.hpp>

std::string PPM::write_header(std::size_t width, std::size_t height)
{
    const std::string MAGIC_NUMBER = "P3\n"; // according to online PPM format
                                             // reference
    const std::string SIZE =
        std::to_string(width) + ' ' + std::to_string(height) + '\n';
    const std::string MAX_COLOR = "255\n";

    return MAGIC_NUMBER + SIZE + MAX_COLOR;
}

std::string PPM::to_string(const Color &color)
{
    const auto RED_CLAMPED = std::max(0.0, std::min(1.0, color.red()));
    const auto GREEN_CLAMPED = std::max(0.0, std::min(1.0, color.green()));
    const auto BLUE_CLAMPED = std::max(0.0, std::min(1.0, color.blue()));

    const auto RED_VALUE =
        static_cast<std::size_t>(std::round(RED_CLAMPED * MAX_COLOR_VALUE));
    const auto GREEN_VALUE =
        static_cast<std::size_t>(std::round(GREEN_CLAMPED * MAX_COLOR_VALUE));
    const auto BLUE_VALUE =
        static_cast<std::size_t>(std::round(BLUE_CLAMPED * MAX_COLOR_VALUE));

    return std::string(std::to_string(RED_VALUE) + ' ' +
                       std::to_string(GREEN_VALUE) + ' ' +
                       std::to_string(BLUE_VALUE));
}

void PPM::split_line(std::string &lines_str, const std::size_t limit)
{
    std::string_view window(lines_str.begin(), lines_str.begin() + limit);
    std::size_t target_start = 0;
    std::size_t target_end = std::min(window.find('\n'), limit);
    while (target_end < lines_str.length())
    {
        if (lines_str.at(target_end) == ' ' || lines_str.at(target_end) == '\n')
        {
            lines_str.at(target_end) = '\n';

            target_start = target_end + 1;
            window = std::string_view(lines_str.begin() + target_start,
                                      lines_str.begin() + target_start + limit);
            target_end = target_start + std::min(window.find('\n'), limit);
        }
        else
        {
            target_end = lines_str.rfind(' ', target_end);
        }
    }
}

std::string PPM::write_data(
    const std::vector<Color> &data, const std::size_t &canvas_width)
{
    std::string str;
    std::size_t count = 0;
    for (const auto &color : data)
    {
        str += to_string(color) + ' ';
        ++count;

        if (count == canvas_width)
        {
            str.back() = '\n';
            count = 0;
        }
    }

    constexpr std::size_t LINE_LIMIT = 70;
    split_line(str, LINE_LIMIT);

    return str;
}
