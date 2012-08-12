cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(ogl-samples-pack)
enable_testing()

#CMAKE_BUILD_TOOL

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
	message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

################################
# Add common source 

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common")

################################
# Add GLEXT 

find_package(OpenGL)
if(NOT OPENGL_FOUND)
	message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)

################################
# Add GLEW

set(GLEW_DIRECTORY glew-1.9.0)

if(MSVC AND NOT CMAKE_CL_64)
	set(GLEW_BINARY_DIRECTORY "win32-vc")
endif(MSVC AND NOT CMAKE_CL_64)

if(MSVC AND CMAKE_CL_64)
	set(GLEW_BINARY_DIRECTORY "win64-vc")
endif(MSVC AND CMAKE_CL_64)

add_definitions(-DGLEW_STATIC)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLEW_DIRECTORY}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLEW_DIRECTORY}/lib/${GLEW_BINARY_DIRECTORY})

if(WIN32)
	set(GLEW_LIBRARY glew32s)
elseif(UNIX)
	set(GLEW_LIBRARY GLEW)
endif(WIN32)

################################
# Add OpenCL

set(CL_DIRECTORY cl-1.2)

if(MSVC AND NOT CMAKE_CL_64)
	set(CL_LIBRARY_DIRECTORY "x86")
	set(CL_BINARY_DIRECTORY "x86/OpenCL.dll")
endif(MSVC AND NOT CMAKE_CL_64)

if(MSVC AND CMAKE_CL_64)
	set(CL_LIBRARY_DIRECTORY "x86_64")
	set(CL_BINARY_DIRECTORY "x86_64/OpenCL.dll")
endif(MSVC AND CMAKE_CL_64)

set(CL_BINARY ${CMAKE_CURRENT_SOURCE_DIR}/external/${CL_DIRECTORY}/bin/${CL_BINARY_DIRECTORY}) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${CL_DIRECTORY})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${CL_DIRECTORY}/lib/${CL_LIBRARY_DIRECTORY})

set(CL_LIBRARY OpenCL)

################################
# Add GLM 

set(GLM_DIRECTORY glm-0.9.3.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_DIRECTORY})

################################
# Add GLI 

set(GLI_DIRECTORY gli-0.3.1.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLI_DIRECTORY})

################################
# Add FreeGLUT

set(FREEGLUT_DIRECTORY freeglut-2.8.0)

if(MSVC AND NOT CMAKE_CL_64)
	set(FREEGLUT_BINARY_DIRECTORY "win32-vc")
endif(MSVC AND NOT CMAKE_CL_64)

if(MSVC AND CMAKE_CL_64)
	set(FREEGLUT_BINARY_DIRECTORY "win64-vc")
endif(MSVC AND CMAKE_CL_64)

add_definitions(-DFREEGLUT_STATIC)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${FREEGLUT_DIRECTORY})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${FREEGLUT_DIRECTORY}/lib/${FREEGLUT_BINARY_DIRECTORY})

if(WIN32)
	set(FREEGLUT_LIBRARY freeglut_static)
elseif(UNIX)
	set(FREEGLUT_LIBRARY freeglut)
endif(WIN32)

################################
# Add OpenGL ES

set(ES_DIRECTORY gles-2.0)

if(MSVC AND NOT CMAKE_CL_64)
	set(ES_BINARY_DIRECTORY "win32-vc")
endif(MSVC AND NOT CMAKE_CL_64)

if(MSVC AND CMAKE_CL_64)
	set(ES_BINARY_DIRECTORY "win64-vc")
endif(MSVC AND CMAKE_CL_64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${ES_DIRECTORY})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${ES_DIRECTORY}/lib/${ES_BINARY_DIRECTORY})

set(ES_LIBRARY libGLESv2)

################################
# Add EGL

set(EGL_DIRECTORY egl-1.4)

if(MSVC AND NOT CMAKE_CL_64)
	set(EGL_BINARY_DIRECTORY "win32-vc")
endif(MSVC AND NOT CMAKE_CL_64)

if(MSVC AND CMAKE_CL_64)
	set(EGL_BINARY_DIRECTORY "win64-vc")
endif(MSVC AND CMAKE_CL_64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${EGL_DIRECTORY})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${EGL_DIRECTORY}/lib/${EGL_BINARY_DIRECTORY})

set(EGL_LIBRARY libEGL)

################################
# Add libraries to executables

set(BINARY_FILES 
	${GL_LIBRARY} 
	${CL_LIBRARY}
	${FREEGLUT_LIBRARY} 
	${GLEW_LIBRARY}
	${GLM_LIBRARY} 
	${GLI_LIBRARY})

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
# function to create a project for the sample in the solution

function(createSample NAME)
	file(GLOB PROJECT_SOURCE *.cpp)
	file(GLOB_RECURSE PROJECT_SHADER *.vert *.frag *.geom *.cont *.eval *.glsl *.vs *.fs *.gs *.ps *.es)
	file(GLOB PROJECT_INLINE *.inl)
	file(GLOB PROJECT_HEADER *.hpp)
	file(GLOB PROJECT_TEXT readme.txt)

	source_group("Text Files" FILES ${PROJECT_TEXT})
	source_group("Inline Files" FILES ${PROJECT_INLINE})
	source_group("Shader Files" FILES ${PROJECT_SHADER})

	add_executable(${NAME} ${PROJECT_SOURCE} ${PROJECT_INLINE} ${PROJECT_HEADER} ${PROJECT_SHADER} ${PROJECT_TEXT})
	add_custom_command(
		TARGET ${NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
	add_custom_command(
		TARGET ${NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_BINARY} ${CMAKE_CURRENT_BINARY_DIR})

	target_link_libraries(${NAME} ${GL_LIBRARY} ${CL_LIBRARY} ${GLEW_LIBRARY} ${FREEGLUT_LIBRARY} ${ASSIMP_LIBRARY})
endfunction(createSample)

function(createSampleWGL NAME)
	file(GLOB PROJECT_SOURCE *.cpp)
	file(GLOB_RECURSE PROJECT_SHADER *.vert *.frag *.geom *.cont *.eval *.glsl)
	file(GLOB PROJECT_INLINE *.inl)
	file(GLOB PROJECT_HEADER *.hpp)
	file(GLOB PROJECT_TEXT readme.txt)

	source_group("Text Files" FILES ${PROJECT_TEXT})
	source_group("Inline Files" FILES ${PROJECT_INLINE})
	source_group("Shader Files" FILES ${PROJECT_SHADER})

	add_executable(${NAME} WIN32 ${PROJECT_SOURCE} ${PROJECT_INLINE} ${PROJECT_HEADER} ${PROJECT_SHADER} ${PROJECT_TEXT})
	add_custom_command(
		TARGET ${NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
	add_custom_command(
		TARGET ${NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_BINARY} ${CMAKE_CURRENT_BINARY_DIR})

	target_link_libraries(${NAME} ${GL_LIBRARY} ${CL_LIBRARY} ${GLEW_LIBRARY} ${FREEGLUT_LIBRARY} ${ASSIMP_LIBRARY})
endfunction(createSampleWGL)

################################
# Add subdirectory

add_subdirectory(samples)
