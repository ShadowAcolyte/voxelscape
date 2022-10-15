cmake_minimum_required (VERSION 3.18)

project (voxelscape VERSION 0.1)

add_subdirectory (lib/glad)
add_subdirectory (lib/glfw)
add_subdirectory (lib/glm)
add_subdirectory (lib/spdlog)
add_subdirectory (lib/stb)

set (SRC
 "src/main.cpp"
 "src/application.h" "src/application.cpp"
 "src/config.h" "src/config.cpp"
 "src/log.h" "src/log.cpp"

 "src/input/input.h"
 "src/input/mouse_input.cpp"
 "src/input/keyboard_input.cpp"

 "src/graphics/mesh.h"
 "src/graphics/camera.h" "src/graphics/camera.cpp"
 "src/graphics/window.h" "src/graphics/window.cpp"
 "src/graphics/shader.h" "src/graphics/shader.cpp" )

add_executable (voxelscape ${SRC})

target_compile_features (voxelscape PRIVATE cxx_std_17)
target_link_libraries (voxelscape PRIVATE glad glfw glm stb spdlog::spdlog)

file (COPY ./shaders DESTINATION ./)
file (COPY ./assets DESTINATION ./)
