cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(06 C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(aoc main.c)
target_include_directories(aoc PUBLIC "${PROJECT_SOURCE_DIR}/..")

message(STATUS "${PROJECT_BINARY_DIR}")
message(STATUS "${PROJECT_SOURCE_DIR}")
