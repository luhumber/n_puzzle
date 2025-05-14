cmake_minimum_required(VERSION 3.16)
project(N-Puzzle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/MainWindow.ui
    src/core/PuzzleParser/PuzzleParser.cpp
    src/core/PuzzleParser/PuzzleParser.h
    src/core/Solver/Solver.cpp
    src/core/Solver/Solver.h
    src/core/Metrics/Metrics.cpp
    src/core/Metrics/Metrics.h
    src/core/Node/Node.cpp
    src/core/Node/Node.h
    src/core/Algorithms/SearchAlgorithm.cpp
    src/core/Algorithms/SearchAlgorithm.h
    src/core/Algorithms/AStar/AStar.cpp
    src/core/Algorithms/AStar/AStar.h
    src/core/Algorithms/IDAStar/IDAStar.cpp
    src/core/Algorithms/IDAStar/IDAStar.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/gui
    src/core
    src/core/PuzzleParser
    src/core/Algorithms
    src/core/Algorithms/AStar
    src/core/Algorithms/IDAStar
    src/core/Algorithms/SearchAlgorithm
    src/core/Node
    src/core/Metrics
    src/core/Solver
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Concurrent)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/file_to_copy/npuzzle-gen.py
    ${CMAKE_CURRENT_BINARY_DIR}/npuzzle-gen.py
)
