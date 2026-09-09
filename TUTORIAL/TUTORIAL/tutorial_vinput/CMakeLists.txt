cmake_minimum_required(VERSION 4.2.3)
project(vinput)

set(compile_options -Wall -Wextra)
set(compile_features c_std_99)

add_subdirectory(library)
add_subdirectory(project)
