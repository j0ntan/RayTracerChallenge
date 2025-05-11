add_library(Float_compare utility/Float_compare.cpp)
target_include_directories(Float_compare PUBLIC utility)

add_library(Tuple Tuple.cpp)
target_link_libraries(Tuple PRIVATE Float_compare)

add_library(Point Point.cpp)
target_link_libraries(Point PUBLIC Tuple PRIVATE Float_compare)

add_library(Vector Vector.cpp)
target_link_libraries(Vector PUBLIC Point PRIVATE Float_compare)

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
