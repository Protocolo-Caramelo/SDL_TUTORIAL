add_executable(${CMAKE_PROJECT_NAME})

target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        main.c
        app/app.c
        app/ball.c
        app/balls.c
        app/guideline.c
        app/infos.c
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
# target_link_options(
#     ${CMAKE_PROJECT_NAME}
#     PRIVATE
#         -fsanitize=address,undefined
#         -fno-omit-frame-pointer
#     )
target_compile_features(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        ${compile_features}
    )
