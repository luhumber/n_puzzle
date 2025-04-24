cmake_minimum_required(VERSION 3.16)
project(MonProjetQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/MainWindow.ui
    src/maths/Algorithms.cpp
    src/maths/Algorithms.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/gui
    src/maths
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/file_to_copy/npuzzle-gen.py
    ${CMAKE_CURRENT_BINARY_DIR}/npuzzle-gen.py
)
