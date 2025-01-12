cmake_minimum_required(VERSION 3.16)
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE COMMON_SOURCES_FILES 
  ${COMMON_DIR}/*.c* 
  ${COMMON_DIR}/*.h* 
  ${EXTERN_DIR}/sdl/*.h*
)
add_library(Common STATIC ${COMMON_SOURCES_FILES})

# Setup tab sources
foreach(_source IN ITEMS ${COMMON_SOURCES_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${COMMON_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    string(REPLACE "..\\" "" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

set_target_properties(Common PROPERTIES FOLDER "Common")
target_include_directories(Common PUBLIC "${COMMON_DIR}" "${EXTERN_DIR}/sdl/include")

set_target_properties(Common PROPERTIES LINK_FLAGS CXX)