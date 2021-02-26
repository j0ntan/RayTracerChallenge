#include <gtest/gtest.h>
#include <math/Sphere.hpp>

TEST(Sphere, defaultConstruct) { Sphere s; }

TEST(Sphere, constructWithRadiusAndOrigin) { Sphere s(1.0, Point()); }
