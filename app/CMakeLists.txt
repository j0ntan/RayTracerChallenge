add_executable(projectile projectile.cpp)
target_link_libraries(projectile Vector Canvas)

add_executable(analog_clock analog_clock.cpp)
target_link_libraries(analog_clock Transformations Point Canvas)

add_executable(sphere_shadow sphere_shadow.cpp)
target_link_libraries(sphere_shadow Canvas Transformations Interactions)
