add_library(Ray Ray.cpp)
target_link_libraries(Ray Point Vector)
add_executable(test_Ray Ray.test.cpp)
target_link_libraries(test_Ray Ray gtest_main)

add_library(Transformations Transformations.cpp)
target_link_libraries(Transformations Matrix Ray)
add_executable(test_Transformations Transformations.test.cpp)
target_link_libraries(test_Transformations Transformations gtest_main)

add_library(Sphere Sphere.cpp)
target_link_libraries(Sphere Point Vector Matrix)
add_executable(test_Sphere Sphere.test.cpp)
target_link_libraries(test_Sphere Sphere Transformations gtest_main)

add_library(Intersection Intersection.cpp)
target_link_libraries(Intersection Sphere)
add_executable(test_Intersection Intersection.test.cpp)
target_link_libraries(test_Intersection Intersection gtest_main)

add_library(Intersections Intersections.cpp)
target_link_libraries(Intersections Intersection Transformations)
add_executable(test_Intersections Intersections.test.cpp)
target_link_libraries(test_Intersections Intersections gtest_main)

add_library(Light Light.cpp)
target_link_libraries(Light Point Color)
add_executable(test_Light Light.test.cpp)
target_link_libraries(test_Light Light gtest_main)

add_library(Material Material.cpp)
target_link_libraries(Material Color)
add_executable(test_Material Material.test.cpp)
target_link_libraries(test_Material Material gtest_main)