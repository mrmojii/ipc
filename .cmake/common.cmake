set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SUPPRESS_REGENERATION true) # remove 'ZERO_CHECK' target

set(IGNORE_WARNINGS "/ignore:4099") # pdb missing
if(NOT CMAKE_MSVC_RUNTIME_LIBRARY)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

include(GNUInstallDirs)

# Preprocessor definitions
add_compile_definitions(UNICODE WIN32_LEAN_AND_MEAN NOMINMAX) # for windows.h (mostly)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>") # set utf-8 for ide and compiler (used for translations)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# lib extern
set(EXTERN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)