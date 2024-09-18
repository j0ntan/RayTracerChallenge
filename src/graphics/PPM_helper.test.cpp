#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <string>

#include "PPM_helper.hpp"
#include <graphics/Canvas.hpp>

TEST(writePPMHeader, callFunction) {
  Canvas c(10, 20);
  std::string header = write_header(c);
}

TEST(writePPMHeader, endsWithNewline) {
  Canvas c(10, 20);
  std::string header = write_header(c);
  char expected = '\n';
  ASSERT_EQ(header.back(), expected);
}

TEST(writePPMHeader, containsExactlyThreeLines) {
  Canvas c(10, 20);
  std::string header = write_header(c);
  int newline_count = std::count(header.begin(), header.end(), '\n'),
      expected = 3;
  ASSERT_EQ(newline_count, expected);
}

TEST(writePPMHeader, convertMagicNumberToText) {
  Canvas c(10, 20);
  std::string header = write_header(c);
  std::string expected = "P3\n";
  ASSERT_EQ(header.substr(0, 3), expected);
}

TEST(writePPMHeader, convertSizeToText) {
  Canvas c(10, 20);
  std::string header = write_header(c);
  std::string expected = "10 20\n";
  ASSERT_EQ(header.substr(3, 6), expected);
}

TEST(writePPMHeader, convertMaxColorToText) {
  Canvas c(10, 20);
  std::string header = write_header(c);
  std::string expected = "255\n";
  ASSERT_EQ(header.substr(9, 4), expected);
}

TEST(ColorToString, callFunction) {
  Color color;
  std::string color_str = to_string(color);
}

TEST(ColorToString, convertDefaultColor) {
  Color color;
  std::string expected = "0 0 0";
  ASSERT_EQ(to_string(color), expected);
}

TEST(ColorToString, scaleUpEachColor) {
  Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
  std::string expected_red = "255 0 0", expected_green = "0 255 0",
              expected_blue = "0 0 255";
  ASSERT_EQ(to_string(red), expected_red);
  ASSERT_EQ(to_string(green), expected_green);
  ASSERT_EQ(to_string(blue), expected_blue);
}

TEST(ColorToString, clampValuesOutOfRange) {
  Color color(0.5, -1.2, 2.0);
  std::string expected = "128 0 255";
  ASSERT_EQ(to_string(color), expected);
}

TEST(CanvasToString, callFunction) {
  Canvas canvas(1, 1);
  std::string canvas_str = to_string(canvas);
}

TEST(CanvasToString, convertSingleDefaultPixel) {
  Canvas canvas(1, 1);
  std::string expected = "0 0 0\n";
  ASSERT_EQ(to_string(canvas), expected);
}

TEST(CanvasToString, convertSingleSpecifiedPixel) {
  Canvas canvas(1, 1);
  canvas.write(0, 0, Color(1, 0.5, 0.8));
  std::string expected = "255 128 204\n";
  ASSERT_EQ(to_string(canvas), expected);
}

TEST(CanvasToString, convertRowOfTwoDefaultPixels) {
  Canvas canvas(2, 1);
  std::string expected = "0 0 0 0 0 0\n";
  ASSERT_EQ(to_string(canvas), expected);
}

TEST(CanvasToString, convertColumnOfTwoDefaultPixels) {
  Canvas canvas(1, 2);
  std::string expected = "0 0 0 0 0 0\n";
  ASSERT_EQ(to_string(canvas), expected);
}

TEST(CanvasToString, splitLineWithLengthOf72IntoTwoLines) {
  // Each default pixel converts to "0 0 0 ", which is 6 chars, so 12 pixels
  // will guarantee a string that extends 70 chars
  Canvas canvas(12, 1);

  auto canvas_str = to_string(canvas);
  auto first_half = canvas_str.substr(0, 66),
       second_half = canvas_str.substr(66);

  ASSERT_EQ(std::count(canvas_str.begin(), canvas_str.end(), '\n'), 2);
  ASSERT_EQ(first_half.back(), '\n');
  std::string expected = "0 0 0\n";
  ASSERT_EQ(second_half, expected);
}

TEST(CanvasToString, splitLargerCanvas) {
  Canvas canvas(100, 100);

  auto canvas_str = to_string(canvas);

  const int CHARS_PER_PIXEL = 6;
  const int TOTAL_PIXELS = canvas.width * canvas.height;
  const int TOTAL_CHARS = TOTAL_PIXELS * CHARS_PER_PIXEL;
  const int CHARS_PER_LINE = 66;
  const int NEWLINES_COUNT = (TOTAL_CHARS / CHARS_PER_LINE) + 1;
  ASSERT_EQ(std::count(canvas_str.begin(), canvas_str.end(), '\n'),
            NEWLINES_COUNT);
}
