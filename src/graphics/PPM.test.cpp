#include <graphics/PPM.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <unordered_set>

TEST(PPM, createMagicIdentifiers) {
  auto bin = MagicIdentifier::BINARY;
  auto txt = MagicIdentifier::ASCII;
}

TEST(PPM, constructWithSpecifiedSizeAndIdentifier) {
  PPM ppm(100, 100, MagicIdentifier::ASCII);
}

TEST(PPM, constructWithDefaultSizeAndIdentifier) { PPM ppm; }

TEST(PPM, getMagicIdentifier) {
  PPM ppm;
  const std::string ID = ppm.magic;
}

TEST(PPM, matchGivenIdentifier) {
  PPM ppm1(1, 1, MagicIdentifier::ASCII), ppm2(1, 1, MagicIdentifier::BINARY);
  ASSERT_EQ(ppm1.magic, "P3");
  ASSERT_EQ(ppm2.magic, "P6");
}

TEST(PPM, matchDefaultIdentifer) {
  PPM ppm;
  ASSERT_EQ(ppm.magic, "P6");
}

TEST(PPM, getWidthAndHeight) {
  PPM ppm;
  size_t width = ppm.width;
  size_t height = ppm.height;
}

TEST(PPM, matchDefaultWidthAndHeight) {
  PPM ppm;
  ASSERT_EQ(ppm.width, 100);
  ASSERT_EQ(ppm.height, 100);
}

TEST(PPM, matchGivenWidthAndHeight) {
  PPM ppm(123, 456);
  ASSERT_EQ(ppm.width, 123);
  ASSERT_EQ(ppm.height, 456);
}

TEST(PPM, getMaxColor) {
  PPM ppm;
  size_t max_color = ppm.max_color;
  size_t static_max_color = PPM::max_color;
}

TEST(PPM, maxColorIs255) { ASSERT_EQ(PPM::max_color, 255); }

TEST(PPM, getHeader) {
  const PPM ppm;
  std::string header = ppm.header();
}

TEST(PPM, matchHeaderForDefaultValues) {
  const PPM ppm;
  ASSERT_EQ(ppm.header(), "P6\n"
                          "100 100\n"
                          "255\n");
}

TEST(PPM, matchHeaderWithGivenValues) {
  const PPM ppm(123, 456, MagicIdentifier::ASCII);
  ASSERT_EQ(ppm.header(), "P3\n"
                          "123 456\n"
                          "255\n");
}

TEST(ImageData, readPixelAtRowAndCol) {
  PPM ppm;
  const size_t ROW = 0;
  const size_t COL = 0;
  Pixel p = ppm.at(ROW, COL);
}

TEST(ImageData, getReferenceToSinglePixel) {
  PPM ppm;
  const size_t ROW = 0;
  const size_t COL = 0;
  Pixel &p = ppm.at(ROW, COL);
}

TEST(ImageData, getReferenceToAllPixels) {
  PPM ppm;
  std::unordered_set<Pixel *> references;
  for (size_t row = 0; row < ppm.height; ++row)
    for (size_t col = 0; col < ppm.width; ++col) {
      Pixel *ref = &ppm.at(row, col);
      auto unique_ref = references.insert(ref).second;
      ASSERT_TRUE(unique_ref) << "non-unique reference for Pixel at " << '('
                              << row << ", " << col << ')';
    }
}

bool operator==(const Pixel &lhs, const Pixel &rhs) {
  return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue;
}
bool operator!=(const Pixel &lhs, const Pixel &rhs) { return !(lhs == rhs); }

TEST(ImageData, allPixelsDefaultToZero) {
  PPM ppm;
  for (size_t row = 0; row < ppm.height; ++row)
    for (size_t col = 0; col < ppm.width; ++col)
      ASSERT_EQ(ppm.at(row, col), Pixel());
}

TEST(ImageData, writePixelAtRowAndCol) {
  PPM ppm;
  const size_t ROW = 0;
  const size_t COL = 0;
  ppm.write(ROW, COL, Pixel());
}

TEST(ImageData, writeChangesPixelValue) {
  PPM ppm;
  const size_t ROW = 0;
  const size_t COL = 0;
  const Pixel PIXEL{1, 2, 3};

  ASSERT_EQ(ppm.at(ROW, COL), Pixel());
  ppm.write(ROW, COL, PIXEL);
  ASSERT_EQ(ppm.at(ROW, COL), PIXEL);
}

TEST(ImageData, readingOutOfBoundsDefaultsToEdgePixel) {
  PPM ppm;
  const size_t SIZE = ppm.width;
  const size_t RIGHT_EDGE_INDEX = SIZE - 1, BOTTOM_EDGE_INDEX = SIZE - 1;
  for (size_t i = 0; i < SIZE; ++i) {
    ppm.write(i, RIGHT_EDGE_INDEX, Pixel{i + 1, i + 1, i + 1});
    ppm.write(BOTTOM_EDGE_INDEX, i, Pixel{i + 1, i + 1, i + 1});
  }

  for (size_t i = 0; i < SIZE; ++i) {
    const Pixel EXPECTED = {i + 1, i + 1, i + 1};
    ASSERT_EQ(ppm.at(i, RIGHT_EDGE_INDEX + 1 + i), EXPECTED)
        << "failed to match right edge Pixel at row " << i;
    ASSERT_EQ(ppm.at(BOTTOM_EDGE_INDEX + 1 + i, i), EXPECTED)
        << "failed to match bottom edge Pixel at column " << i;
  }
}

TEST(ImageData, writingOutOfBoundsDefaultsToEdgePixel) {
  PPM ppm;
  const size_t SIZE = ppm.width;
  const size_t RIGHT_EDGE_INDEX = SIZE - 1, BOTTOM_EDGE_INDEX = SIZE - 1;
  for (size_t i = 0; i < SIZE; ++i) {
    ppm.write(i, RIGHT_EDGE_INDEX + 1 + i, Pixel{i + 1, i + 1, i + 1});
    ppm.write(BOTTOM_EDGE_INDEX + 1 + i, i, Pixel{i + 1, i + 1, i + 1});
  }

  for (size_t row = 0; row < ppm.height; ++row)
    for (size_t col = 0; col < ppm.width; ++col)
      if (row == ppm.height - 1 || col == ppm.width - 1)
        ASSERT_NE(ppm.at(row, col), Pixel())
            << "failed to match Pixel at (" << row << ", " << col << ')';
      else
        ASSERT_EQ(ppm.at(row, col), Pixel());
}

TEST(Output, canConvertToString) {
  const PPM ppm;
  auto str = std::string(ppm);
}

TEST(Output, stringContainsHeader) {
  const PPM ppm;
  ASSERT_EQ(std::string(ppm).find(ppm.header()), 0);
}

TEST(Output, stringContainsImageDataAfterHeader) {
  const PPM ppm;
  auto image_data = std::string(ppm).substr(ppm.header().length());
  ASSERT_FALSE(image_data.empty());
}

TEST(Output, matchImageDataPixels) {
  constexpr size_t N = 2;
  std::array<Pixel, N *N> pixels = {
      {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}};
  PPM ppm(N, N);

  auto pixel_it = pixels.begin();
  for (size_t row = 0; row < N; ++row)
    for (size_t col = 0; col < N; ++col)
      ppm.write(row, col, *pixel_it++);

  auto image_data = std::string(ppm).substr(ppm.header().length());
  for (auto &expected_pixel : pixels)
    ASSERT_NE(image_data.find(std::string(expected_pixel)), std::string::npos);
}

TEST(Output, stringContainsAllPixels) {
  PPM ppm;
  auto image_data = std::string(ppm).substr(ppm.header().length());
  std::istringstream stream(image_data);

  const auto PIXEL_STR = std::string(Pixel());
  size_t line_count = 0;
  std::string line;
  while (std::getline(stream, line)) {
    ++line_count;
    ASSERT_EQ(line, PIXEL_STR);
  }

  ASSERT_EQ(line_count, ppm.height * ppm.width);
}

TEST(Output, canConvertToBytes) {
  const PPM ppm;
  std::vector<std::byte> bytes = ppm.bytes();
}

TEST(Output, bytesContainsHeader) {
  const PPM PPM(1, 1);
  const std::vector<std::byte> EXPECTED_BYTES = {
      std::byte{80}, // 'P'
      std::byte{54}, // '6'
      std::byte{10}, // '\n'
      std::byte{49}, // '1'
      std::byte{32}, // ' '
      std::byte{49}, // '1'
      std::byte{10}, // '\n'
      std::byte{50}, // '2'
      std::byte{53}, // '5'
      std::byte{53}, // '5'
      std::byte{10}  // '\n'
  };
  const auto PPM_BYTES = PPM.bytes();

  ASSERT_GE(PPM_BYTES.size(), EXPECTED_BYTES.size());

  for (size_t i = 0; i < EXPECTED_BYTES.size(); ++i)
    ASSERT_EQ(PPM_BYTES[i], EXPECTED_BYTES[i]);
}

TEST(Output, matchWrittenPixelsToBytes) {
  PPM ppm(1, 2);
  ppm.write(0, 0, Pixel{12, 34, 56});
  ppm.write(1, 0, Pixel{21, 43, 65});

  const std::vector<std::byte> EXPECTED_BYTES = {std::byte{12}, std::byte{34},
                                                 std::byte{56}, std::byte{21},
                                                 std::byte{43}, std::byte{65}};

  auto header_size = ppm.header().size();
  auto bytes = ppm.bytes();

  ASSERT_EQ(bytes.size(), header_size + EXPECTED_BYTES.size());

  for (size_t i = 0; i < EXPECTED_BYTES.size(); ++i)
    ASSERT_EQ(bytes[header_size + i], EXPECTED_BYTES[i]);
}
