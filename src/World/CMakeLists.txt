add_library(PointLight INTERFACE PointLight.hpp)
target_link_libraries(PointLight INTERFACE Point Color)

add_library(Material Material.cpp)
target_link_libraries(Material Color StripePattern)

add_library(MaterialCmp INTERFACE utility/MaterialCmp.hpp)
target_include_directories(MaterialCmp INTERFACE utility)
target_link_libraries(MaterialCmp INTERFACE Material Float_compare)

add_library(World World.cpp)
target_link_libraries(World PUBLIC Shape PointLight
    PRIVATE Sphere Transformations)

add_library(Camera Camera.cpp)
target_link_libraries(Camera PUBLIC Ray Canvas World PRIVATE Interactions)

# Tests
add_executable(test_PointLight PointLight.test.cpp)
target_link_libraries(test_PointLight PointLight GTest::gtest_main)
gtest_discover_tests(test_PointLight)

add_executable(test_Material Material.test.cpp)
target_link_libraries(test_Material Material GTest::gtest_main)
gtest_discover_tests(test_Material)

add_executable(test_World World.test.cpp)
target_link_libraries(test_World Transformations MaterialCmp Interactions
    GTest::gtest_main)
gtest_discover_tests(test_World)

add_executable(test_Camera Camera.test.cpp)
target_link_libraries(test_Camera Camera  World
    GTest::gtest_main)
gtest_discover_tests(test_Camera)
