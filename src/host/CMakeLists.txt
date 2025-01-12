# Find sources
set(HOST_SOURCE_DIR "${IPC_DIR}/host")

file(GLOB_RECURSE HOST_SOURCES_FILES 
  ${HOST_SOURCE_DIR}/*.c* 
  ${HOST_SOURCE_DIR}/*.h* 
)

# Create targets
add_executable(Host ${HOST_SOURCES_FILES})

# Setup tab sources
foreach(_source IN ITEMS ${HOST_SOURCES_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${HOST_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    string(REPLACE "..\\" "" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# Properties
set_target_properties(Host PROPERTIES FOLDER "Host")
set_target_properties(Host PROPERTIES LINK_FLAGS "${IGNORE_WARNINGS}") # Missing pdb

target_include_directories(Host PUBLIC "${HOST_SOURCE_DIR}" "${EXTERN_DIR}/boost")
target_link_directories(Host PUBLIC "${EXTERN_DIR}/sdl/lib")
target_link_libraries(Host PRIVATE Common Boost SDL2 SDL2main SDL2test)