cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(ogl-samples-pack-4.0.0)

##########################
# Setup binary directory

if(MSVC)
	if(MSVC_VERSION EQUAL 1400)
		set(BINARY_DIRECTORY "win32-vc2005")
	endif(MSVC_VERSION EQUAL 1400)
	if(MSVC_VERSION EQUAL 1500)
		set(BINARY_DIRECTORY "win32-vc2008")
	endif(MSVC_VERSION EQUAL 1500)	
	if(MSVC_VERSION EQUAL 1600)
		set(BINARY_DIRECTORY "win32-vc2010")
	endif(MSVC_VERSION EQUAL 1600)
else(MSVC)
	set(BINARY_DIRECTORY "unknowned")
endif(MSVC)

#####################
# Add common source 

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common")

###########
# Add SDL 

set(SDL_VERSION "SDL-1.3.0-4429")
set(SDL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${SDL_VERSION})

if(MSVC)
	link_directories("${SDL_DIRECTORY}/binary/${BINARY_DIRECTORY}")
	execute_process(COMMAND cmake -E copy ${SDL_DIRECTORY}/binary/${BINARY_DIRECTORY}/SDL.dll ${CMAKE_CURRENT_BINARY_DIR}/build/release/SDL.dll)
	execute_process(COMMAND cmake -E copy ${SDL_DIRECTORY}/binary/${BINARY_DIRECTORY}/SDL.dll ${CMAKE_CURRENT_BINARY_DIR}/build/debug/SDL.dll)
	execute_process(COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/build/release)
	execute_process(COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/build/debug)
else(MSVC)
	if(DEFINED CMAKE_BUILD_TYPE)

	else()
		set(CMAKE_BUILD_TYPE Release)
	endif()
	
	set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")

    execute_process(COMMAND sh ./autogen.sh	WORKING_DIRECTORY ${SDL_DIRECTORY})
    execute_process(COMMAND ./configure --prefix=${SDL_DIRECTORY} WORKING_DIRECTORY ${SDL_DIRECTORY})
    execute_process(COMMAND make WORKING_DIRECTORY ${SDL_DIRECTORY})
    execute_process(COMMAND make install WORKING_DIRECTORY ${SDL_DIRECTORY})
    link_directories("${SDL_DIRECTORY}/lib")
endif(MSVC)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/${SDL_VERSION}/include")

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
	set(GLEW_VERSION "glew-1.5.4")
	set(GLEW_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLEW_VERSION})

	add_definitions(-DGLEW_STATIC)
	include_directories("${GLEW_DIRECTORY}/include")
	link_directories("${GLEW_DIRECTORY}/lib/${BINARY_DIRECTORY}")
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
set(GLI_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLI_VERSION})

include_directories("${GLI_DIRECTORY}")

################################
# Add libraries to executables

if(MSVC)
	set(BINARY_FILES "SDL" "SDLmain" "glew32s" "OpenGL32")
endif(MSVC)
if(APPLE)
    set(BINARY_FILES "SDL" "SDLmain" "../libGL.dylib")
	#/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
endif(APPLE)
#if(UNIX and NOT APPLE)
#	set(BINARY_FILES "SDL" "SDLmain" "GL")
#endif(UNIX and not APPLE)

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
add_custom_target(
	${TARGET_DATA_COPY}
 	COMMAND pwd)
# 	COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

set(OGL_DATA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

################################
# Add definitions

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS)

################################
# Add subdirectory

add_subdirectory(samples)
