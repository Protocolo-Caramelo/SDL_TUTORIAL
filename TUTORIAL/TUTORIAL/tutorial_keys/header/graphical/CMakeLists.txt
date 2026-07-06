add_library(graphical)
target_sources(
    graphical
    PUBLIC
        FILE_SET graphical
        TYPE HEADERS
        FILES
            graphical.h

    PRIVATE
        GInit.h
        GWindow.h
        GTexture.h
        GInit.c
        GWindow.c
        GTexture.c
    )

target_link_libraries(
    graphical
    PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
    )

target_compile_options(
    graphical
    PRIVATE
        ${compile_options}
)
target_compile_features(
    graphical
    PRIVATE
        ${compile_features}
)

