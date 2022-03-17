cmake_minimum_required(VERSION 3.16.3)

project(RPSearch)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(DFS)
target_include_directories(${PROJECT_NAME} PUBLIC DFS) #For the sub folder called DFS
target_link_directories(${PROJECT_NAME} PUBLIC DFS) #To add the library in the main without specyfing the path (name of the folder)
target_link_libraries(${PROJECT_NAME} dfs) #name of the librarie in the cmakelist