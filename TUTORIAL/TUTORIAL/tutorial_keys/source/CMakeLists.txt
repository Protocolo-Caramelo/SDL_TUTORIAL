add_executable(${CMAKE_PROJECT_NAME})

target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        main.c
        app/app.c
        app/bullet.c
    )
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        app/
    )

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
        graphical
        m
    )
