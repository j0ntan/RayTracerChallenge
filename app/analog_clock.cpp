#include <array>
#include <cmath>
#include <numbers>
#include <Math/Point.hpp>
#include <Math/Transformations.hpp>
#include <Graphics/Canvas.hpp>

/**
 * @note We will align the world coordinate system with the canvas xy-plane,
 * such that the positive x,y,z-directions in world space are to the right,
 * downwards, & towards the canvas viewer, respectively.
 *
 */

/**
 * @brief The count of hour marks on a standard analog clock
 *
 */
const std::size_t MARKS_COUNT = 12;

/**
 * @brief Generate the hour-mark points on a virtual clock, in the xy-plane
 *
 * The points will have a radius of 1 from the center of the clock.
 *
 * @return std::array<Point, MARKS_COUNT> Array of hour-mark points
 */
std::array<Point, MARKS_COUNT> generate_clock_points()
{
    std::array<Point, MARKS_COUNT> points;

    // move all points up 1 unit in y-direction
    for (auto &point : points)
    {
        point = translation(0, 1, 0) * point;
    }

    // rotate points to align with hour marks
    const double ANGLE_BETWEEN_HOURS = (2 * std::numbers::pi) / 12;
    std::size_t num_of_rotations = 0;
    for (auto &point : points)
    {
        point = rotation_z(ANGLE_BETWEEN_HOURS * num_of_rotations++) * point;
    }

    return points;
}

/**
 * @brief Maps a set of points from world coordinates to canvas coordinates
 *
 * @param points Set of points
 * @param canvas_size Side length of the square canvas, in pixels
 */
void map_to_canvas(
    std::array<Point, MARKS_COUNT> &points, std::size_t canvas_size)
{
    const auto ORIGIN_TRANSLATOR =
        translation(canvas_size / 2, canvas_size / 2, 0);

    const double SCALE_FACTOR = (canvas_size / 2) * (3.0 / 4.0);
    const auto POINT_SCALER = scaling(SCALE_FACTOR, SCALE_FACTOR, 0);

    /**
     * @note Apply scaling first to map points to canvas coordinate system,
     * then apply the translation, which is already based on canvas coordinates.
     *
     */
    const auto T = ORIGIN_TRANSLATOR * POINT_SCALER;

    for (auto &point : points)
    {
        // apply transformation
        point = T * point;

        // round coordinate to nearest integer value
        point = Point(std::round(point.x()), std::round(point.y()), 0);
    }
}

int main()
{
    const std::size_t CANVAS_SIZE = 200;
    Canvas canvas(CANVAS_SIZE, CANVAS_SIZE);

    auto points = generate_clock_points();
    map_to_canvas(points, CANVAS_SIZE);

    // write points to canvas
    for (auto &point : points)
    {
        canvas.write_pixel(point.x(), point.y(), Color(1, 1, 1));
    }

    write_PPM_file(canvas, "clock");
}
