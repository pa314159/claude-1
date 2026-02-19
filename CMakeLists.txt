cmake_minimum_required(VERSION 3.15)
project(plugin_loader C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

include_directories(${CMAKE_SOURCE_DIR})

# Main executable
add_executable(main main.c loader.c)
target_link_libraries(main dl)

# Plugins
add_library(hello SHARED plugins/hello.c)
add_library(goodbye SHARED plugins/goodbye.c)

set_target_properties(hello goodbye PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)

# Test executable
add_executable(test_plugin plugins/test.c loader.c)
target_link_libraries(test_plugin dl)

enable_testing()
add_test(NAME plugins COMMAND test_plugin)
