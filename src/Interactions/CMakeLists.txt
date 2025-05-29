add_library(Interactions Interactions.cpp)
target_include_directories(Interactions PUBLIC .)
target_link_libraries(Interactions Ray Sphere)

add_library(Lighting Lighting.cpp)
target_include_directories(Lighting PUBLIC .)
target_link_libraries(Lighting PRIVATE Material PointLight Vector)

# Tests
add_executable(test_Intersection Intersection.test.cpp)
target_link_libraries(test_Intersection Interactions GTest::gtest_main)
gtest_discover_tests(test_Intersection)

add_executable(test_Lighting Lighting.test.cpp)
target_link_libraries(test_Lighting Lighting GTest::gtest_main)
gtest_discover_tests(test_Lighting)
