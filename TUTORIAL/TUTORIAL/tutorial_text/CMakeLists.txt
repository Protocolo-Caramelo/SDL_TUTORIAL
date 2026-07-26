cmake_minimum_required(VERSION 4.2.3)
project(text)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
if(NOT DEFINED compilation_mode)
    set(compilation_mode "NORMAL")
endif()

if(${compilation_mode} MATCHES "NORMAL")
    set(compile_options -Wall -Wextra -D COMPILATION_NORMAL)
    set(compile_features c_std_99)
elseif(${compilation_mode} MATCHES "DEVQUOTE")
    set(compile_options -Wall -Wextra -D COMPILATION_DEVQUOTE)
    set(compile_features c_std_99)
endif()

add_subdirectory(library)
add_subdirectory(source)
