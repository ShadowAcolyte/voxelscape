cmake_minimum_required (VERSION 3.18)

project (voxelscape VERSION 0.1)

add_subdirectory (dependencies/glad)
add_subdirectory (dependencies/glfw)
add_subdirectory (dependencies/glm)
add_subdirectory (dependencies/spdlog)
add_subdirectory (dependencies/stb)

set (SRC
 "src/main.cpp"
 "src/config.h" "src/config.cpp"
 "src/util/log.h" "src/util/log.cpp"
 "src/util/time.h" "src/util/time.cpp"
 "src/input/input.h"
 "src/input/mouse_input.cpp"
 "src/input/keyboard_input.cpp"
 "src/graphics/window.h" "src/graphics/window.cpp"
 "src/graphics/shader.h" "src/graphics/shader.cpp"
 "src/graphics/camera.h" "src/graphics/camera.cpp"
 "src/world/block/block.h" "src/world/block/block.cpp"
 "src/world/block/blockid.h"
 "src/world/chunk/chunk.h" "src/world/chunk/chunk.cpp"
 "src/world/chunk/chunk_constants.h"
 "src/world/world.h" "src/world/world.cpp"
 "src/world/direction.h")

add_executable (voxelscape ${SRC})

target_compile_features (voxelscape PRIVATE cxx_std_17)
target_link_libraries (voxelscape PRIVATE glad glfw glm stb spdlog::spdlog)

file (COPY ./shaders DESTINATION ./)
file (COPY ./textures DESTINATION ./)
