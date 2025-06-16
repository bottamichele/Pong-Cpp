# ----- glad -----
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

# ----- glfw -----
set(GLFW_INSTALL OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_LIBRARY_TYPE STATIC)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)