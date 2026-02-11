cmake_minimum_required(VERSION 3.10)
project(csc222-game VERSION 0.1 LANGUAGES CXX)

# Top-level CMake for the course project
# - Adds the dungeongame subdirectory which contains the student-friendly
#   per-project CMake. Students can run these commands from the repo root:
#     mkdir -p build
#     cmake -S . -B build
#     cmake --build build --target dungeongame_exe
# - For Visual Studio (multi-config generator) examples are printed by the
#   subdirectory CMake.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to control tests from the top-level invocation as well
option(BUILD_TESTS "Build project tests" ON)

# Add the dungeongame module
add_subdirectory(dungeongame)

# Helpful top-level message
message(STATUS "Top-level project: ${PROJECT_NAME}")
message(STATUS "To configure: cmake -S . -B build")
message(STATUS "To build: cmake --build build --target dungeongame_exe")
