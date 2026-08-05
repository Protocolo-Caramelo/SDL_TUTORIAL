add_library(utf8)
target_sources(
    utf8
    PUBLIC
        FILE_SET utf8
        TYPE HEADERS
        FILES
            utf8.h

    PRIVATE
        ./utf8.c
)

target_compile_options(
    utf8
    PRIVATE
        ${compile_options}
)
target_compile_features(
    utf8
    PRIVATE
        ${compile_features}
)
