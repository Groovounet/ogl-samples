cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(ogl-samples-pack-4.1.2)

##########################
# Setup binary directory

if(MSVC AND NOT CMAKE_CL_64)
	if(MSVC_VERSION EQUAL 1500)
		set(BINARY_DIRECTORY "win32-vc2008")
	endif(MSVC_VERSION EQUAL 1500)	
	if(MSVC_VERSION EQUAL 1600)
		set(BINARY_DIRECTORY "win32-vc2010")
	endif(MSVC_VERSION EQUAL 1600)
endif(MSVC AND NOT CMAKE_CL_64)

if(MSVC AND CMAKE_CL_64)
	if(MSVC_VERSION EQUAL 1500)
		set(BINARY_DIRECTORY "win64-vc2008")
	endif(MSVC_VERSION EQUAL 1500)	
	if(MSVC_VERSION EQUAL 1600)
		set(BINARY_DIRECTORY "win64-vc2010")
	endif(MSVC_VERSION EQUAL 1600)
endif(MSVC AND CMAKE_CL_64)

#####################
# Add common source 

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common")

############
# Add GLUT 

if(MSVC)
	set(GLUT_VERSION "freeglut-2.6.0")
	set(GLUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLUT_VERSION})

	add_definitions(-DFREEGLUT_STATIC)
	include_directories("${GLUT_DIRECTORY}")
	link_directories("${GLUT_DIRECTORY}/lib/${BINARY_DIRECTORY}")
endif(MSVC)

############
# Add GLEW 

if(MSVC)
	set(GLEW_VERSION "glew-1.5.6")
	set(GLEW_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLEW_VERSION})

	add_definitions(-DGLEW_STATIC)
	include_directories(${GLEW_DIRECTORY}/include)
	link_directories(${GLEW_DIRECTORY}/lib/${BINARY_DIRECTORY})
endif(MSVC)

############
# Add GLEXT 

if(APPLE)
    set(GL_VERSION "GL")
    set(GL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/OpenGL.framework)

        include_directories("${GL_DIRECTORY}/Headers")
        link_directories("${GL_DIRECTORY}/Libraries/")
endif(APPLE)

###########
# Add GLM 

set(GLM_VERSION "glm")
set(GLM_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_VERSION})

include_directories("${GLM_DIRECTORY}")

###########
# Add GLI

set(GLI_VERSION "gli")
#set(GLI_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLI_VERSION})
set(GLI_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLI_VERSION})

include_directories("${GLI_DIRECTORY}")

################################
# Add libraries to executables

if(MSVC)
	set(BINARY_FILES "glew32s" "OpenGL32")
elseif(APPLE)
    set(BINARY_FILES "../libGL.dylib")
	#/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
elseif(UNIX)
	set(BINARY_FILES "glut" "GLEW")
endif()

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

set(TARGET_DATA_COPY DATA_COPY)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	add_custom_target(
		${TARGET_DATA_COPY}
 		COMMAND cmake -E echo "In source build")
else(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	add_custom_target(
		${TARGET_DATA_COPY}
 		COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

set(OGL_DATA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

################################
# Add definitions

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS)

################################
# Add subdirectory

add_subdirectory(samples)
