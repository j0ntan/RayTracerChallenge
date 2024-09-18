#include <fstream>
#include <graphics/Canvas.hpp>

#include <gtest/gtest.h>
#include <sstream>

TEST(CanvasConstructor, constructBasicCanvas) {
  const size_t WIDTH = 5, HEIGHT = 3;
  Canvas c(WIDTH, HEIGHT);
}

TEST(CanvasSize, accessWidthAndHeight) {
  const size_t WIDTH = 100, HEIGHT = 100;
  Canvas canvas(WIDTH, HEIGHT);
  size_t canvas_width = canvas.width;
  size_t canvas_height = canvas.height;
}

TEST(CanvasSize, matchInitializedSize) {
  const size_t WIDTH = 100, HEIGHT = 100;
  Canvas canvas(WIDTH, HEIGHT);
  ASSERT_EQ(canvas.width, WIDTH);
  ASSERT_EQ(canvas.height, HEIGHT);
}

TEST(CanvasPixel, accessPixelColor) {
  Canvas canvas{100, 100};
  Color c = canvas.pixel(0, 0);
}

TEST(CanvasConstructor, matchEmptyCanvasDefaultBlackPixels) {
  Canvas canvas{100, 100};
  const Color BLACK{0, 0, 0};
  for (unsigned x = 0; x < canvas.width; ++x)
    for (unsigned y = 0; y < canvas.height; ++y)
      ASSERT_EQ(canvas.pixel(x, y), BLACK);
}

TEST(CanvasWrite, writeToCanvas) {
  Canvas canvas{100, 100};
  const size_t X = 2, Y = 3;
  const Color RED(1, 0, 0);
  canvas.write(X, Y, RED);
}

TEST(CanvasWrite, matchWrittenColors) {
  Canvas canvas{100, 100};
  const Color RED(1, 0, 0), BLUE(0, 1, 0);
  canvas.write(2, 3, RED);
  canvas.write(4, 8, BLUE);
  ASSERT_EQ(canvas.pixel(2, 3), RED);
  ASSERT_EQ(canvas.pixel(4, 8), BLUE);
}

TEST(WritePPM, callFunction) {
  Canvas canvas(1, 1);
  write_PPM(canvas, "filename");
}
