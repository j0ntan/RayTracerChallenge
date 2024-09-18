add_library(Pixel Pixel.cpp)
target_include_directories(Pixel PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(PPM_helper PPM_helper.cpp)
target_include_directories(PPM_helper INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(PPM_helper Canvas)

add_library(Color Color.cpp)
target_link_libraries(Color Tuple)

add_library(Canvas Canvas.cpp)
target_link_libraries(Canvas Color PPM_helper)

add_library(Camera Camera.cpp)
target_link_libraries(Camera Matrix Ray World Canvas)

# Tests
add_executable(test_Pixel Pixel.test.cpp)
target_link_libraries(test_Pixel Pixel GTest::gtest_main)
gtest_discover_tests(test_Pixel)

add_executable(test_Color Color.test.cpp)
target_link_libraries(test_Color Color GTest::gtest_main)
gtest_discover_tests(test_Color)

add_executable(test_PPM_helper PPM_helper.test.cpp)
target_link_libraries(test_PPM_helper PPM_helper GTest::gtest_main)
gtest_discover_tests(test_PPM_helper)

add_executable(test_Canvas Canvas.test.cpp)
target_link_libraries(test_Canvas Canvas GTest::gtest_main)
gtest_discover_tests(test_Canvas)

add_executable(test_Camera Camera.test.cpp)
target_link_libraries(test_Camera Camera Transformations View GTest::gtest_main)
gtest_discover_tests(test_Camera)
