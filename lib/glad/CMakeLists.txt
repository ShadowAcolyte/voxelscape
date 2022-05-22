cmake_minimum_required(VERSION 3.18)

add_library(glad src/glad.c)

target_compile_features(glad PRIVATE c_std_99)
target_include_directories(glad PUBLIC include/)