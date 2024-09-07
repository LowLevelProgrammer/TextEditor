find_package(GTest REQUIRED)

# Include directories for test files
include_directories(${GTEST_INCLUDE_DIRS})

# Define TESTING macro for compilation
# add_definitions(-DTESTING)

# List of test source files
file(GLOB_RECURSE TEST_SOURCE_FILES "*.cpp")

add_executable(TextEditorTests ${TEST_SOURCE_FILES})

# Add source files from the main project that are needed by the tests
# file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}src/*.cpp")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Remove main.cpp from the source list to avoid multiple definition of 'main'
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_sources(TextEditorTests PRIVATE ${SOURCE_FILES})

# Link against Google Test Library
target_link_libraries(TextEditorTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
target_link_libraries(TextEditorTests ${CURSES_LIBRARIES} tinfo)

# Register the test with CTest
add_test(NAME TextEditorTests COMMAND TextEditorTests)
