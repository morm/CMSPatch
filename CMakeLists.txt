project(patcher)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(NtHookEngine)
add_subdirectory(injector)
#add_subdirectory(pemaker7)
#add_subdirectory(remote_injector)

add_dependencies(injector NtHookEngine)
#add_dependencies(remote_injector injector)