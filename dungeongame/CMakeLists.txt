cmake_minimum_required(VERSION 3.10)
project(dungeongame VERSION 0.1 LANGUAGES CXX)

# Export compile commands for IDEs (generates build/compile_commands.json)
# This helps VS Code's C/C++ extension and other tools find include paths
# automatically when CMake is configured.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# CMake for dungeongame
# - Cross-platform by using target-based include directories and generator
#   expressions for output locations (works for Unix Makefiles, Ninja, and
#   Visual Studio multi-config generators).
# - Explicitly lists sources so students can see what's being added to the
#   library instead of using globbing in real projects.
# - Adds simple options and helpful messages for learners.
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Where to put built binaries and libraries. For single-config generators
# (Make, Ninja) CMAKE_RUNTIME_OUTPUT_DIRECTORY is sufficient. For multi-
# config generators (Visual Studio) we also set per-target properties below.
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(LIB_DIR ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})

# Simple options for students to toggle
option(BUILD_TESTS "Build test executable(s)" ON)
option(ENABLE_WARNINGS "Enable compiler warnings" ON)

# Explicit source list (clear for students)
set(DUNGEON_SOURCES
    src/Game.cpp
    src/Character.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Inventory.cpp
    src/EnemySpawner.cpp
    src/ActionHistory.cpp
    src/SpellEvaluator.cpp
)

# Create static library for core game code
add_library(dungeongame_lib STATIC ${DUNGEON_SOURCES})

# Provide include path to consumers of the library (PUBLIC so executables
# that link the library also get the include path).
target_include_directories(dungeongame_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Require C++17 features (helps students understand modern CMake)
target_compile_features(dungeongame_lib PUBLIC cxx_std_17)

# Compiler warnings: use appropriate flags for MSVC vs others
if(ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(dungeongame_lib PRIVATE /W4 /permissive-)
    else()
        target_compile_options(dungeongame_lib PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

# Silence some MSVC warnings about secure CRT in teaching examples
if(MSVC)
    target_compile_definitions(dungeongame_lib PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Main executable that uses the library
add_executable(dungeongame_exe src/main.cpp)
target_link_libraries(dungeongame_exe PRIVATE dungeongame_lib)

# Ensure executables land in the same bin directory for all generators
set_target_properties(dungeongame_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}
)

# Optional: combat test executable
if(BUILD_TESTS)
    add_executable(combat_test_exe tests/combat_test.cpp)
    target_link_libraries(combat_test_exe PRIVATE dungeongame_lib)
    set_target_properties(combat_test_exe PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    )

    # Week 04 unit tests
    add_executable(test_enemy_spawner tests/test_enemy_spawner.cpp)
    target_link_libraries(test_enemy_spawner PRIVATE dungeongame_lib)
    set_target_properties(test_enemy_spawner PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
    add_test(NAME test_enemy_spawner COMMAND test_enemy_spawner)

    add_executable(test_action_undo tests/test_action_undo.cpp)
    target_link_libraries(test_action_undo PRIVATE dungeongame_lib)
    set_target_properties(test_action_undo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
    add_test(NAME test_action_undo COMMAND test_action_undo)

    add_executable(test_spell_eval tests/test_spell_eval.cpp)
    target_link_libraries(test_spell_eval PRIVATE dungeongame_lib)
    set_target_properties(test_spell_eval PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
    add_test(NAME test_spell_eval COMMAND test_spell_eval)

    enable_testing()
    add_test(NAME combat_test COMMAND combat_test_exe)
endif()

# Note: the pointers demo has been integrated into the main game as
# Game::runPointersDemo() (accessible from the in-game menu). The standalone
# `pointers_demo.cpp` source is deprecated and is no longer built as a
# separate executable to avoid confusion and duplicate main() definitions.
# If you want to keep a standalone demo, add a separate target here.

# Helpful messages for students
message(STATUS "dungeongame: build output goes to: ${BIN_DIR}")
message(STATUS "To build on Unix: cmake -S . -B build && cmake --build build --target dungeongame_exe")
message(STATUS "To build on Windows (Visual Studio): cmake -S . -B build -G \"Visual Studio 17 2022\" && cmake --build build --config Release --target dungeongame_exe")
message(STATUS "Use -DBUILD_TESTS=OFF to skip building the test executable if desired")
