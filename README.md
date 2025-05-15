# N-Puzzle

This project provides a complete implementation of the sliding puzzle game (N-Puzzle), featuring a graphical interface and two solving algorithms.

## Overview

The N-Puzzle is a logic game where the goal is to arrange numbered tiles in order by sliding them into an empty space. This project allows you to:
- Generate or load puzzles of various sizes (from 3x3 to 20x20)
- Check the validity and solvability of any configuration
- Automatically solve the puzzle using different search algorithms (A* and IDA*)
- Visualize the solving process through a modern graphical interface (Qt6)

## Main Features

- **Load puzzles** from a file or generate random boards
- **Select the solving algorithm** and heuristic
- **Graphical display** of the puzzle and moves
- **Statistics** on the solving process (number of states explored, time, etc.)
- **Error handling** for invalid or unsolvable puzzles

## Project Structure

- `src/core/`: core solving engine (algorithms, parsing, puzzle logic)
- `src/gui/`: graphical user interface (Qt)
- `test/`: test files and sample puzzles

## Requirements

- Qt 6.x (Widgets, Core, etc.)
- CMake ≥ 3.16
- A C++17 compatible compiler

## Usage

Build the project:

```sh
make
```

Then run the executable from the `build/` directory:
```sh
./N-Puzzle
```

Otherwise, run directly the following to build and run the project:
```sh
make run
```

You can load a puzzle file ([examples](test/)) or generate a random board from the interface.

## Notes

- The project is designed to be easily extensible (new heuristics, algorithms, etc.)
- Algorithms are optimized for reasonably sized puzzle
