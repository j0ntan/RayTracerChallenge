include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(projectile projectile.cpp)
target_link_libraries(projectile Point Vector Canvas)
