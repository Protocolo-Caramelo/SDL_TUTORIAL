cmake_minimum_required(VERSION 4.2.3)
project(SDLWindow)

find_package(SDL2 REQUIRED)

set(compile_options -Wall -Wextra)
set(compile_features "c_std_99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_subdirectory(headers)
add_subdirectory(sources)
