add_library(Ray Ray.cpp)
target_link_libraries(Ray Vector)

add_library(Transformations Transformations.cpp)
target_link_libraries(Transformations Matrix Ray)

add_library(Material Material.cpp)
target_link_libraries(Material Color)

add_library(Sphere Sphere.cpp)
target_link_libraries(Sphere Vector Matrix Material)

add_library(Intersection Intersection.cpp)
target_link_libraries(Intersection Sphere)

add_library(Intersections Intersections.cpp)
target_link_libraries(Intersections Intersection Transformations)

add_library(Light Light.cpp)
target_link_libraries(Light Point Color)

add_library(Lighting Lighting.cpp)
target_link_libraries(Lighting Material Light Vector)

add_library(Computations Computations.cpp)
target_link_libraries(Computations Float_compare Point Sphere Vector
    Intersection)

add_library(World World.cpp)
target_link_libraries(World Light Intersections Computations Lighting)

add_library(View View.cpp)
target_link_libraries(View Point Vector Transformations)

# Tests
add_executable(test_Ray Ray.test.cpp)
target_link_libraries(test_Ray Ray GTest::gtest_main)
gtest_discover_tests(test_Ray)

add_executable(test_Transformations Transformations.test.cpp)
target_link_libraries(test_Transformations Transformations GTest::gtest_main)
gtest_discover_tests(test_Transformations)

add_executable(test_Material Material.test.cpp)
target_link_libraries(test_Material Material GTest::gtest_main)
gtest_discover_tests(test_Material)

add_executable(test_Sphere Sphere.test.cpp)
target_link_libraries(test_Sphere Sphere Transformations GTest::gtest_main)
gtest_discover_tests(test_Sphere)

add_executable(test_Intersection Intersection.test.cpp)
target_link_libraries(test_Intersection Intersection GTest::gtest_main)
gtest_discover_tests(test_Intersection)

add_executable(test_Intersections Intersections.test.cpp)
target_link_libraries(test_Intersections Intersections GTest::gtest_main)
gtest_discover_tests(test_Intersections)

add_executable(test_Light Light.test.cpp)
target_link_libraries(test_Light Light GTest::gtest_main)
gtest_discover_tests(test_Light)

add_executable(test_Lighting Lighting.test.cpp)
target_link_libraries(test_Lighting Lighting GTest::gtest_main)
gtest_discover_tests(test_Lighting)

add_executable(test_World World.test.cpp)
target_link_libraries(test_World World GTest::gtest_main)
gtest_discover_tests(test_World)

add_executable(test_Computations Computations.test.cpp)
target_link_libraries(test_Computations Point Ray Computations Transformations
gtest_main)
gtest_discover_tests(test_Computations)

add_executable(test_View View.test.cpp)
target_link_libraries(test_View View GTest::gtest_main)
gtest_discover_tests(test_View)
