add_library(Color Color.cpp)
target_link_libraries(Color Tuple)

add_library(PPM PPM.cpp)
target_link_libraries(PPM Color)

add_library(Canvas Canvas.cpp)
target_link_libraries(Canvas PRIVATE PPM)

add_library(Pattern INTERFACE Pattern.hpp)
target_link_libraries(Pattern INTERFACE Point Color Matrix)

add_library(StripePattern StripePattern.cpp)
target_link_libraries(StripePattern Pattern)

# Tests
add_executable(test_Color Color.test.cpp)
target_link_libraries(test_Color Color GTest::gtest_main)
gtest_discover_tests(test_Color)

add_executable(test_PPM PPM.test.cpp)
target_link_libraries(test_PPM PPM GTest::gtest_main)
gtest_discover_tests(test_PPM)

add_executable(test_Canvas Canvas.test.cpp)
target_link_libraries(test_Canvas Canvas GTest::gtest_main)
gtest_discover_tests(test_Canvas)

add_executable(test_Pattern Pattern.test.cpp)
target_include_directories(test_Pattern PRIVATE .)
target_link_libraries(test_Pattern Pattern Sphere Transformations
    GTest::gtest_main)
gtest_discover_tests(test_Pattern)

add_executable(test_StripePattern StripePattern.test.cpp)
target_include_directories(test_StripePattern PRIVATE .)
target_link_libraries(test_StripePattern StripePattern Sphere Transformations
    GTest::gtest_main)
gtest_discover_tests(test_StripePattern)
