cmake_minimum_required(VERSION 3.10)
project(TextEditor VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Include directories
include_directories(src/tui/elements src/tui/primitives src/core/commands src/core src/io src/editor src/tui src/application src/)

# Glob all source and header files recursively
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(TextEditor ${SOURCE_FILES})
target_link_libraries(TextEditor ${CURSES_LIBRARIES} tinfo)

# Add test directory
enable_testing()
add_subdirectory(tests)
