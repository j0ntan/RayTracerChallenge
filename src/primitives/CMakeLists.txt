add_library(Point Point.cpp)
target_link_libraries(Point PRIVATE Float_compare)
add_executable(test_Point Point.test.cpp)
target_link_libraries(test_Point Point gtest_main)
