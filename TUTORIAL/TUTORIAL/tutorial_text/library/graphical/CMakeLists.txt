add_library(
    graphical
    STATIC
)

target_sources(
    graphical
    PUBLIC
        FILE_SET graphical
        TYPE HEADERS
        FILES
        graphical.h

        GCommons.h
        GInit.h
        GTexture.h
        GWindow.h

        GText/GText.h
        GText/GTextCache.h
        GText/GTextCacheGlyph.h
        GText/GTextCharFormat.h
        GText/GTextConfig.h
        GText/GTextSpacing.h

        GTest/GTest.h

    PRIVATE
        GInit.c
        GWindow.c
        GTexture.c

        GText/GText.c
        GText/GTextCache.c
        GText/GTextCacheGlyph.c
        GText/GTextConfig.c
        GText/GTextSpacing.c

        GTest/GText.c
        GTest/GTextCG.c
        GTest/GTextCache.c
    )
target_link_libraries(
    graphical
    PUBLIC
        SDL2
        SDL2_image
        SDL2_ttf
        utf8
        uthash
    )

target_include_directories(
    graphical
    PRIVATE
        GText
        GTest
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
