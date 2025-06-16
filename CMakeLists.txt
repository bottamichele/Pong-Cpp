cmake_minimum_required(VERSION 3.10)

project(Pong VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----- third party -----
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# ----- pong project -----
file(GLOB_RECURSE PONG_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp src/*.hpp)

add_executable(pong ${PONG_SOURCE})

target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)

target_link_libraries(pong glad glfw)

set_target_properties(pong PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/release
)