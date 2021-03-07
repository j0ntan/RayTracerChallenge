#include <algorithm>
#include <array>
#include <graphics/Canvas.hpp>
#include <iostream>
#include <scene/Transformations.hpp>

const std::size_t CLOCK_MARKS = 12;

using clk_pts_t = std::array<Point, CLOCK_MARKS>;

clk_pts_t generate_clk_unit_points() {
  // Start with array of points in 12 o'clock position.
  const Point TWELVE_O_CLOCK(0, 0, 1);
  clk_pts_t points;
  std::fill(points.begin(), points.end(), TWELVE_O_CLOCK);

  // Rotate each point according to clock angles
  double clk_angle = 0;
  std::transform(points.begin(), points.end(), points.begin(),
                 [&](Point point) {
                   Matrix<4> rotation = rotate_y(clk_angle);
                   clk_angle += PI / 6;
                   return Point(rotation * point);
                 });

  return points;
}

clk_pts_t generate_clock_points(unsigned int canvas_size) {
  // Start with 12 points in unit circle.
  auto clk_points = generate_clk_unit_points();

  // Scale up each point.
  const unsigned int CLOCK_RADIUS = canvas_size / 2 * (3.0 / 4);
  Matrix<4> scaling = scale(CLOCK_RADIUS, CLOCK_RADIUS, CLOCK_RADIUS);
  std::transform(clk_points.begin(), clk_points.end(), clk_points.begin(),
                 [&](Point point) { return Point(scaling * point); });

  // Translate each point to encircle center of canvas.
  Matrix<4> translation = translate(canvas_size / 2, 0, canvas_size / 2);
  std::transform(clk_points.begin(), clk_points.end(), clk_points.begin(),
                 [&](Point point) { return Point(translation * point); });

  return clk_points;
}

int main() {
  const unsigned int CANVAS_SIDE_LENGTH = 200;
  Canvas canvas(CANVAS_SIDE_LENGTH, CANVAS_SIDE_LENGTH);

  auto points = generate_clock_points(CANVAS_SIDE_LENGTH);

  for (auto point : points)
    canvas.write(point.z(), point.x(), Color(1, 1, 1));

  canvas.to_ppm_file("clock");
}
