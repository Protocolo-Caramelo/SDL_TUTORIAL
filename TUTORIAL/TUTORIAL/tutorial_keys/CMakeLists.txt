cmake_minimum_required(VERSION 4.2.3)
project(keys)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(compile_options -Wall -Wextra)
set(compile_features c_std_99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_subdirectory(header)
add_subdirectory(source)
