#include <gtest/gtest.h>
#include <scene/Light.hpp>

TEST(Light, constructWithPointAndColor) { Light light(Point(), Color()); }
