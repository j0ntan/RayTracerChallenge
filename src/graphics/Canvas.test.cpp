#include <graphics/Canvas.hpp>
#include <gtest/gtest.h>
#include <sstream>

TEST(Canvas, constructBasicCanvas) {
  const unsigned int WIDTH = 5, HEIGHT = 3;
  Canvas c(WIDTH, HEIGHT);
}

TEST(Canvas, widthAndHeightAreInitialized) {
  const unsigned int WIDTH = 100, HEIGHT = 100;
  Canvas canvas{WIDTH, HEIGHT};
  ASSERT_EQ(canvas.width, WIDTH);
  ASSERT_EQ(canvas.height, HEIGHT);
}

TEST(Canvas, getColorFromPixel) {
  Canvas canvas{100, 100};
  Color c = canvas.pixel(0, 0);
}

TEST(Canvas, allPixelsDefaultToBlack) {
  Canvas canvas{100, 100};
  const Color black{0, 0, 0};
  for (unsigned x = 0; x < canvas.width; ++x)
    for (unsigned y = 0; y < canvas.height; ++y)
      ASSERT_EQ(canvas.pixel(x, y), black);
}

TEST(Canvas, writeColorToPixelAtXYCoordinates) {
  Canvas canvas{100, 100};
  const Color red(1, 0, 0), blue(0, 1, 0);
  canvas.write(2, 3, red);
  canvas.write(4, 8, blue);
  ASSERT_EQ(canvas.pixel(2, 3), red);
  ASSERT_EQ(canvas.pixel(4, 8), blue);
}

TEST(PPM, writeOutputFile) {
  Canvas canvas{100, 100};
  canvas.to_ppm_file("sample_ppm");
}
