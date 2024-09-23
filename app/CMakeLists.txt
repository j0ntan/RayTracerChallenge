add_executable(projectile projectile.cpp)
target_link_libraries(projectile Point Vector Canvas)

add_executable(analog_clock analog_clock.cpp)
target_link_libraries(analog_clock Point Transformations Canvas)

add_executable(sphere_shadow sphere_shadow.cpp)
target_link_libraries(sphere_shadow Canvas Transformations Ray Sphere
    Intersections)

add_executable(3D_sphere 3D_sphere.cpp)
target_link_libraries(3D_sphere Canvas Transformations Sphere Ray Light
    Lighting Intersections)

add_executable(3_spheres 3_spheres.cpp)
target_link_libraries(3_spheres Canvas Camera View)
