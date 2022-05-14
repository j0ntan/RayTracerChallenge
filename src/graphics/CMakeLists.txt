add_library(Pixel Pixel.cpp)
target_include_directories(Pixel PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(PPM PPM.cpp)
target_link_libraries(PPM Pixel)

add_library(Color Color.cpp)
target_link_libraries(Color Tuple)

add_library(Canvas Canvas.cpp)
target_link_libraries(Canvas Color PPM)

add_library(Camera Camera.cpp)
target_link_libraries(Camera Matrix)

# Tests
add_executable(test_Pixel Pixel.test.cpp)
target_link_libraries(test_Pixel Pixel gtest_main)

add_executable(test_Color Color.test.cpp)
target_link_libraries(test_Color Color gtest_main)

add_executable(test_PPM PPM.test.cpp)
target_link_libraries(test_PPM PPM gtest_main)

add_executable(test_Canvas Canvas.test.cpp)
target_link_libraries(test_Canvas Canvas gtest_main)

add_executable(test_Camera Camera.test.cpp)
target_link_libraries(test_Camera Camera gtest_main)
