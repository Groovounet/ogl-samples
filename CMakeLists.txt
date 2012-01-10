cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(ogl-samples-pack)
enable_testing()

#CMAKE_BUILD_TOOL

################################
# Add common source 

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common")

################################
# Add package

macro(addExternalPackageGTC NAME DIRECTORY)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/external/${DIRECTORY}/util)
	set(${NAME}_PACKAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/${DIRECTORY})

	find_package(${NAME})
	if(NOT ${NAME}_FOUND)
		message("ERROR: ${NAME} not found")
	endif(NOT ${NAME}_FOUND)
endmacro(addExternalPackageGTC)

################################
# Add GLEXT 

find_package(OpenGL)
find_package(GLUT)
if(NOT OPENGL_FOUND)
	message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)

################################
# Add External package

if(MSVC)
    addExternalPackageGTC("GLEW" "glew-1.7.0")
    addExternalPackageGTC("FREEGLUT" "freeglut-2.6.0")
endif(MSVC)
addExternalPackageGTC("GLM" "glm-0.9.3.0")
addExternalPackageGTC("GLI" "gli-0.3.1.0")

################################
# Add libraries to executables

if(APPLE)
set(BINARY_FILES 
	${OPENGL_LIBRARY} 
	${GLM_LIBRARY} 
	${GLI_LIBRARY})
else(APPLE)
set(BINARY_FILES 
	${OPENGL_LIBRARY} 
	${FREEGLUT_LIBRARY} 
	${GLEW_LIBRARY}
	${GLM_LIBRARY} 
        ${GLI_LIBRARY})
endif(APPLE)

################################
# Add output directory

if(MSVC)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/)
else(MSVC)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/debug )
	else(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/release )
	endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(MSVC)

################################
# Add custom target to copy all data

if(APPLE)
	add_custom_target(
		${TARGET_DATA_COPY}
 		COMMAND ls)

else(APPLE)
	set(TARGET_DATA_COPY DATA_COPY)
	if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
		add_custom_target(
			${TARGET_DATA_COPY}
 			COMMAND ${CMAKE_COMMAND} -E echo "In source build")
	else(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
		add_custom_target(
			${TARGET_DATA_COPY}
 			COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
	endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
endif(APPLE)

set(OGL_DATA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

################################
# Add options

option(OGL_SAMPLES_STATUS "OGL_SAMPLES_STATUS" OFF)
if(OGL_SAMPLES_STATUS)
	add_definitions(-DGLF_AUTO_STATUS)
endif()

################################
# Add definitions

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

################################
# Add subdirectory

add_subdirectory(samples)
