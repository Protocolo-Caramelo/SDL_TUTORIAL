add_executable(${CMAKE_PROJECT_NAME})

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        graphical
    )
target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        main.c
        app/app.c
    )
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        app/
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

