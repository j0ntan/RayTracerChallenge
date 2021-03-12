add_library(Color Color.cpp)
target_link_libraries(Color Tuple)

add_library(Canvas Canvas.cpp)
target_link_libraries(Canvas Color)

# Tests
add_executable(test_Color Color.test.cpp)
target_link_libraries(test_Color Color gtest_main)

add_executable(test_Canvas Canvas.test.cpp)
target_link_libraries(test_Canvas Canvas gtest_main)
