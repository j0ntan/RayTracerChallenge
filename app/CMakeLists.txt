add_executable(projectile projectile.cpp)
target_link_libraries(projectile Vector Canvas)

add_executable(analog_clock analog_clock.cpp)
target_link_libraries(analog_clock Transformations Point Canvas)

add_executable(sphere_shadow sphere_shadow.cpp)
target_link_libraries(sphere_shadow Canvas Transformations Interactions)

add_executable(3D_sphere 3D_sphere.cpp)
target_link_libraries(3D_sphere Lighting Interactions Transformations  Canvas)

add_executable(3_spheres 3_spheres.cpp)
target_link_libraries(3_spheres Transformations Camera)

add_executable(hexagonal_planes hexagonal_planes.cpp)
target_link_libraries(hexagonal_planes Plane Transformations Camera)

FetchContent_Declare(PerlinNoise
    GIT_REPOSITORY  https://github.com/Reputeless/PerlinNoise
    GIT_TAG         master
    GIT_SHALLOW     TRUE
    UPDATE_DISCONNECTED TRUE
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(PerlinNoise)
add_executable(mixed_patterns mixed_patterns.cpp)
target_include_directories(mixed_patterns PRIVATE ${perlinnoise_SOURCE_DIR})
target_link_libraries(mixed_patterns Plane Transformations StripePattern
    RingPattern Camera)
