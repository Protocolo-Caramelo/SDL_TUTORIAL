add_library(graphical)
target_sources(
    graphical
    PUBLIC
        FILE_SET graphical
        TYPE HEADERS
        FILES
            graphical_win.h
            graphical_winConsts.h
            graphical_init.h

    PRIVATE
        graphical_win.c
        graphical_init.c
    )
target_link_libraries(
    graphical
    PUBLIC
        SDL2::SDL2
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
