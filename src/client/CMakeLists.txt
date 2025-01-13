# Find sources
set(CLIENT_SOURCE_DIR "${IPC_DIR}/client")
message(${IPC_DIR})
file(GLOB_RECURSE CLIENT_SOURCES_FILES 
  ${CLIENT_SOURCE_DIR}/*.c* 
  ${CLIENT_SOURCE_DIR}/*.h* 
)

# Create targets
add_executable(Client WIN32 ${CLIENT_SOURCES_FILES})

# Setup tab sources
foreach(_source IN ITEMS ${CLIENT_SOURCES_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CLIENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    string(REPLACE "..\\" "" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# Properties
set_target_properties(Client PROPERTIES FOLDER "Client")
set_target_properties(Client PROPERTIES LINK_FLAGS "${IGNORE_WARNINGS}") # Missing pdb

target_include_directories(Client PUBLIC "${CLIENT_SOURCES_FILES}" "${EXTERN_DIR}/boost")
target_link_directories(Client PUBLIC "${EXTERN_DIR}/sdl/lib")
target_link_libraries(Client PRIVATE Common Boost SDL2 SDL2main SDL2test)