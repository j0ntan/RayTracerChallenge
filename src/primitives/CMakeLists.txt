add_library(Point Point.cpp)
target_link_libraries(Point PRIVATE Float_compare)
add_executable(test_Point Point.test.cpp)
target_link_libraries(test_Point Point gtest_main)

add_library(Vector Vector.cpp)
target_link_libraries(Vector PRIVATE Float_compare Point)
add_executable(test_Vector Vector.test.cpp)
target_link_libraries(test_Vector Vector gtest_main)
