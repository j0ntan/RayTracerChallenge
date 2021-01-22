add_executable(projectile projectile.cpp)
target_link_libraries(projectile Point Vector Canvas)

add_executable(analog_clock analog_clock.cpp)
target_link_libraries(analog_clock Transformations Canvas)
