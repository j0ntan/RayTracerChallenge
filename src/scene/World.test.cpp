#include <gtest/gtest.h>
#include <scene/World.hpp>

TEST(World, defaultConstruct) { World w; }

TEST(World, initialWorldIsEmpty) {
  World w;
  ASSERT_TRUE(w.objects().empty());
  ASSERT_TRUE(w.light_sources().empty());
}
