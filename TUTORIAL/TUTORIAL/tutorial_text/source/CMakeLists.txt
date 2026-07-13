add_executable(${CMAKE_PROJECT_NAME})
file(GLOB SOURCES_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/app/*.c")

message(${SOURCES_MAIN})
target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        main.c
        ${SOURCES_MAIN}
    )
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        app/header
    )
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        graphical
        m
        SDL2
        SDL2_image
    )

target_compile_options(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        ${compile_options}
    )
target_compile_features(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        ${compile_features}
    )
