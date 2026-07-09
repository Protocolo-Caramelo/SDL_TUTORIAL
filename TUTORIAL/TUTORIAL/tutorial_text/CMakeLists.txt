cmake_minimum_required(VERSION 4.2.3)
project(text)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(compile_options -Wall -Wextra)
set(compile_features c_std_99)

add_subdirectory(library)
add_subdirectory(source)
