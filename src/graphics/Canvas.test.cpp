#include <fstream>
#include <graphics/Canvas.hpp>
#include <graphics/PPM.hpp>
#include <gtest/gtest.h>
#include <sstream>

TEST(Canvas, constructBasicCanvas) {
  const size_t WIDTH = 5, HEIGHT = 3;
  Canvas c(WIDTH, HEIGHT);
}

TEST(Canvas, widthAndHeightAreInitialized) {
  const size_t WIDTH = 100, HEIGHT = 100;
  Canvas canvas(WIDTH, HEIGHT);
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

TEST(PPM, convertToPPM) {
  const Canvas canvas{100, 100};
  PPM ppm = canvas.to_PPM(MagicIdentifier::ASCII);
}

TEST(PPM, matchWrittenColors) {
  Canvas canvas{1, 2};

  canvas.write(0, 0, Color(1, 0, 0));
  canvas.write(0, 1, Color(0, 1, 0));

  ASSERT_EQ(std::string(canvas.to_PPM(MagicIdentifier::ASCII)),
            "P3\n1 2\n255\n255 0 0\n0 255 0\n");
}

TEST(PPM, writeAsciiPPMFile) {
  const Canvas canvas(1, 1);
  canvas.write_PPM("sample_ppm", MagicIdentifier::ASCII);
  std::ifstream ppmFile("sample_ppm.ppm");
  ASSERT_TRUE(ppmFile.good());
}
