cmake_minimum_required(VERSION 3.16)
set(BOOST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE BOOST_SOURCES_FILES 
  ${EXTERN_DIR}/boost/*.h* 
  ${BOOST_DIR}/*.c* 
)
add_library(Boost STATIC ${BOOST_SOURCES_FILES})

# Setup tab sources
foreach(_source IN ITEMS ${BOOST_SOURCES_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${BOOST_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    string(REPLACE "..\\" "" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

set_target_properties(Boost PROPERTIES FOLDER "Boost")
target_include_directories(Boost PUBLIC "${BOOST_DIR} ${EXTERN_DIR}/boost")

set_target_properties(Boost PROPERTIES LINK_FLAGS CXX)