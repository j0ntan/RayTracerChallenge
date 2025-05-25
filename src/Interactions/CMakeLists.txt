add_library(Interactions Interactions.cpp)
target_include_directories(Interactions PUBLIC .)
target_link_libraries(Interactions Ray)


# Tests
add_executable(test_Intersection Intersection.test.cpp)
target_link_libraries(test_Intersection Interactions GTest::gtest_main)
gtest_discover_tests(test_Intersection)
