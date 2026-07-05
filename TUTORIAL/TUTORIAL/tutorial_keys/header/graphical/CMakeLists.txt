add_library(graphical)

target_sources(
    graphical
    PUBLIC
        FILE_SET graphical
        TYPE HEADERS
        FILES
            GInit.h
            GTexture.h
            GWindow.h
            graphical.h

    PRIVATE
        GInit.c
        GWindow.c
        GTexture.c
    )
