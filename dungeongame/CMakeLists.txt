cmake_minimum_required(VERSION 3.10)
project(dungeongame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put generated binaries in build/ (so executables are in build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect sources
file(GLOB ALL_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Exclude main.cpp from the library
list(REMOVE_ITEM ALL_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Create a library from core sources (Game, Character, Player, Enemy)
add_library(dungeongame_lib STATIC ${ALL_SOURCES})

target_include_directories(dungeongame_lib PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Main executable (uses library)
add_executable(dungeongame ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(dungeongame PRIVATE dungeongame_lib)

# Combat test executable
add_executable(combat_test ${PROJECT_SOURCE_DIR}/tests/combat_test.cpp)
target_link_libraries(combat_test PRIVATE dungeongame_lib)

target_include_directories(combat_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Optional: enable warnings on both targets
if(MSVC)
    target_compile_options(dungeongame_lib PRIVATE /W4 /permissive-)
else()
    target_compile_options(dungeongame_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()
