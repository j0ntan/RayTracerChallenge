add_library(Float_compare utility/Float_compare.cpp)
target_include_directories(Float_compare PUBLIC utility)

add_library(Tuple Tuple.cpp)
target_link_libraries(Tuple PRIVATE Float_compare)

add_library(Point Point.cpp)
target_link_libraries(Point PUBLIC Tuple PRIVATE Float_compare)

add_library(Vector Vector.cpp)
target_link_libraries(Vector PUBLIC Point PRIVATE Float_compare)

add_library(Matrix Matrix.cpp)
target_link_libraries(Matrix PUBLIC Tuple PRIVATE Float_compare)

add_library(Transformations Transformations.cpp)
target_link_libraries(Transformations Matrix Vector)

add_library(Ray Ray.cpp)
target_link_libraries(Ray Vector Matrix)

add_library(Shape Shape.cpp)
target_link_libraries(Shape PUBLIC Ray Material)

add_library(Sphere Sphere.cpp)
target_link_libraries(Sphere PUBLIC Matrix Vector Material Shape
    PRIVATE Transformations)

# Tests
add_executable(test_Float_compare utility/Float_compare.test.cpp)
target_link_libraries(test_Float_compare Float_compare GTest::gtest_main)
gtest_discover_tests(test_Float_compare)

add_executable(test_Tuple Tuple.test.cpp)
target_link_libraries(test_Tuple Tuple Vector GTest::gtest_main)
gtest_discover_tests(test_Tuple)

add_executable(test_Point Point.test.cpp)
target_link_libraries(test_Point Point GTest::gtest_main)
gtest_discover_tests(test_Point)

add_executable(test_Vector Vector.test.cpp)
target_link_libraries(test_Vector Vector GTest::gtest_main)
gtest_discover_tests(test_Vector)

add_executable(test_Matrix Matrix.test.cpp)
target_link_libraries(test_Matrix Matrix GTest::gtest_main)
gtest_discover_tests(test_Matrix)

add_executable(test_Transformations Transformations.test.cpp)
target_link_libraries(test_Transformations Transformations GTest::gtest_main)
gtest_discover_tests(test_Transformations)

add_executable(test_Ray Ray.test.cpp)
target_link_libraries(test_Ray Ray Transformations GTest::gtest_main)
gtest_discover_tests(test_Ray)

add_executable(test_Sphere Sphere.test.cpp)
target_link_libraries(test_Sphere Sphere MaterialCmp Transformations
    Interactions GTest::gtest_main)
gtest_discover_tests(test_Sphere)

add_executable(test_Shape Shape.test.cpp)
target_link_libraries(test_Shape Shape MaterialCmp Transformations Interactions
    GTest::gtest_main)
gtest_discover_tests(test_Shape)
