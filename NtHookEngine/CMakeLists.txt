project(NtHookEngine)
cmake_minimum_required(VERSION 2.8)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_library(NtHookEngine SHARED NtHookEngine.cpp distorm.h)
target_link_libraries(NtHookEngine distorm_x86.lib)