cmake_minimum_required(VERSION 3.16.3)
project(RPSearch)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Stack_and_queue)

include_directories(. Stack_and_queue)

add_executable(maze_solver main.cpp)

