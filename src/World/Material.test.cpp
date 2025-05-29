#include <MaterialCmp.hpp>
#include <World/Material.hpp>
#include <gtest/gtest.h>

/*
Scenario: The default material
    Given m <- material()
    Then m.color = color(1, 1, 1)
        And m.ambient = 0.1
        And m.diffuse = 0.9
        And m.specular = 0.9
        And m.shininess = 200.0
*/
TEST(MaterialComponents, matchDefaultMaterialValues)

{
    auto m = Material();

    ASSERT_EQ(m.color, Color(1, 1, 1));
    ASSERT_FLOAT_EQ(m.ambient, 0.1);
    ASSERT_FLOAT_EQ(m.diffuse, 0.9);
    ASSERT_FLOAT_EQ(m.specular, 0.9);
    ASSERT_FLOAT_EQ(m.shininess, 200.0);
}
