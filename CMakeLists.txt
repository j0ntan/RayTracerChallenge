cmake_minimum_required(VERSION 4.0.1)

project(RayTracerChallenge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

# Download googletest & add to project
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         main
    GIT_SHALLOW     TRUE
    UPDATE_DISCONNECTED TRUE
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(googletest)

# Add googletest targets
include(GoogleTest)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIR})

add_subdirectory(src/Math)
add_subdirectory(src/Graphics)
add_subdirectory(src/Interactions)
add_subdirectory(src/World)
add_subdirectory(app)
