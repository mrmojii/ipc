cmake_minimum_required(VERSION 3.16)

if (NOT DEFINED PROJECT_NAME)
project(IPC C CXX)
endif()

set(IPC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("IPC_DIR = ${IPC_DIR}")

# Subs
add_subdirectory(boost)             # Target: Boost.lib
add_subdirectory(common)            # Target: Common.lib
add_subdirectory(host)              # Target: Host.exe
add_subdirectory(client)            # Target: Client.exe