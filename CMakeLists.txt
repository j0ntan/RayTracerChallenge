cmake_minimum_required(VERSION 3.16)

project(RayTracerChallenge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

# Download googletest & add to project
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         main
    UPDATE_DISCONNECTED TRUE
)
FetchContent_MakeAvailable(googletest)

# Add googletest targets
include(GoogleTest)

add_subdirectory(src)

add_subdirectory(app)
