project(injector)
cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
add_definitions(-DUNICODE -D_UNICODE)
add_library(injector SHARED main.cpp main.h)
target_link_libraries(injector NtHookEngine.lib)