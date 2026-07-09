add_library(graphical)
file(GLOB GRAPHICAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB GRAPHICAL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

target_sources(
    graphical
    PUBLIC
        FILE_SET graphical
        TYPE HEADERS
        FILES
        ${GRAPHICAL_HEADERS}

    PRIVATE
        ${GRAPHICAL_SOURCES}
    )
target_link_libraries(
    graphical
    PUBLIC
        SDL2
        SDL2_image
        SDL2_ttf
    )

target_compile_options(
    graphical
    PUBLIC
        ${compile_options}
    )
target_compile_features(
    graphical
    PUBLIC
        ${compile_features}
    )
