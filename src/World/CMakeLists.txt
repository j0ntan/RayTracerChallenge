add_library(PointLight INTERFACE ${INCLUDE_DIR}/World/PointLight.hpp)
target_link_libraries(PointLight INTERFACE Point Color)

add_library(Material INTERFACE ${INCLUDE_DIR}/World/Material.hpp)
target_link_libraries(Material INTERFACE Color)

add_library(MaterialCmp INTERFACE MaterialCmp.hpp)
target_include_directories(MaterialCmp INTERFACE .)
target_link_libraries(MaterialCmp INTERFACE Material Float_compare)

# Tests
add_executable(test_PointLight PointLight.test.cpp)
target_link_libraries(test_PointLight PointLight GTest::gtest_main)
gtest_discover_tests(test_PointLight)

add_executable(test_Material Material.test.cpp)
target_link_libraries(test_Material Material MaterialCmp GTest::gtest_main)
gtest_discover_tests(test_Material)
