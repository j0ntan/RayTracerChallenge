add_library(Float_compare Float_compare.cpp)
target_include_directories(Float_compare PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Tests
add_executable(test_Float_compare Float_compare.test.cpp)
target_link_libraries(test_Float_compare Float_compare gtest_main)
