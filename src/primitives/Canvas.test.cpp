#include <gtest/gtest.h>
#include <primitives/Canvas.hpp>

class Canvas_F : public ::testing::Test {
public:
  const unsigned int WIDTH = 100, HEIGHT = 100;
  Canvas canvas{WIDTH, HEIGHT};
};

TEST_F(Canvas_F, constructBasicCanvas) { Canvas c(WIDTH, HEIGHT); }

TEST_F(Canvas_F, accessWidthAndHeight) {
  unsigned int w = canvas.width;
  unsigned int h = canvas.height;
}

TEST_F(Canvas_F, widthAndHeightAreInitialized) {
  ASSERT_EQ(canvas.width, WIDTH);
  ASSERT_EQ(canvas.height, HEIGHT);
}

TEST_F(Canvas_F, accessPixelAtXYCoordinate) {
  const unsigned int X = 0, Y = 0;
  canvas.pixel(X, Y);
}

TEST_F(Canvas_F, getColorFromPixel) { Color c = canvas.pixel(0, 0); }

TEST_F(Canvas_F, allPixelsDefaultToBlack) {
  const Color black{0, 0, 0};
  for (unsigned x = 0; x < WIDTH; ++x)
    for (unsigned y = 0; y < HEIGHT; ++y)
      ASSERT_EQ(canvas.pixel(x, y), black);
}

TEST_F(Canvas_F, writeColorToPixelAtXYCoordinates) {
  canvas.write(0, 0, Color());
}

TEST_F(Canvas_F, readBackWrittenColor) {
  const Color red(1, 0, 0);
  canvas.write(0, 0, red);
  ASSERT_EQ(canvas.pixel(0, 0), red);
}

TEST_F(Canvas_F, writeAndReadDifferentColors) {
  const Color red(1, 0, 0), blue(0, 1, 0);
  canvas.write(2, 3, red);
  canvas.write(4, 8, blue);
  ASSERT_EQ(canvas.pixel(2, 3), red);
  ASSERT_EQ(canvas.pixel(4, 8), blue);
}
