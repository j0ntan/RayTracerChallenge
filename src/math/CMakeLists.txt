add_library(Tuple INTERFACE)
target_link_libraries(Tuple INTERFACE Float_compare)

add_library(Matrix Matrix.cpp)
target_link_libraries(Matrix Tuple)

add_library(Point Point.cpp)
target_link_libraries(Point Tuple)

add_library(Vector Vector.cpp)
target_link_libraries(Vector Point)

# Tests
add_executable(test_Tuple Tuple.test.cpp)
target_link_libraries(test_Tuple Tuple GTest::gtest_main)
gtest_discover_tests(test_Tuple)

add_executable(test_Matrix Matrix.test.cpp)
target_link_libraries(test_Matrix Matrix GTest::gtest_main)
gtest_discover_tests(test_Matrix)

add_executable(test_Point Point.test.cpp)
target_link_libraries(test_Point Point GTest::gtest_main)
gtest_discover_tests(test_Point)

add_executable(test_Vector Vector.test.cpp)
target_link_libraries(test_Vector Vector GTest::gtest_main)
gtest_discover_tests(test_Vector)
