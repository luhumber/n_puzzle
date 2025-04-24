cmake_minimum_required(VERSION 3.16)
project(MonProjetQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    MainWindow.ui
    Algorithms.h
    Algorithms.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/npuzzle-gen.py
    ${CMAKE_CURRENT_BINARY_DIR}/npuzzle-gen.py
)
