cmake_minimum_required (VERSION 3.18)

project (voxelscape VERSION 0.1)

add_subdirectory (dependencies/glad)
add_subdirectory (dependencies/glfw)
add_subdirectory (dependencies/glm)
add_subdirectory (dependencies/spdlog)
add_subdirectory (dependencies/stb)

set (SRC
 "src/main.cpp"
 "src/log.h" "src/log.cpp"
 "src/graphics/window.h" "src/graphics/window.cpp"
 "src/graphics/shader.h" "src/graphics/shader.cpp"
 "src/world/block/block.h" "src/world/block/block.cpp"
 "src/world/chunk/chunk.h" "src/world/chunk/chunk.cpp"
 "src/world/world.h" "src/world/world.cpp"
 "src/world/chunk/chunk_constants.h" "src/world/direction.h" "src/world/block/blockid.h")

add_executable (voxelscape ${SRC})

target_compile_features (voxelscape PRIVATE cxx_std_17)
target_link_libraries (voxelscape PRIVATE glad glfw glm stb spdlog::spdlog)

file (COPY ./shaders DESTINATION ./)
file (COPY ./textures DESTINATION ./)
