cmake_minimum_required(VERSION 3.16)

project(IPC C CXX)
add_compile_definitions(REPO_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

include(.cmake/common.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR}/Debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR}/Release/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR}/Debug/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR}/Release/bin)

add_subdirectory(src)