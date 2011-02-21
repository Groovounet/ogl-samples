cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(gli)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/glm-0.9.0.7")

add_subdirectory(gli)
#add_subdirectory(doc)
#add_subdirectory(sample)
add_subdirectory(test)
