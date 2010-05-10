cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(ogl-samples-pack-2.1)

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

set(SDL_VERSION "sdl-1.3.0-5206") 
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
# Add GLEW 

set(GLEW_VERSION "glew-1.5.3") 
set(GLEW_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLEW_VERSION})

if(MSVC)
	include_directories("${GLEW_DIRECTORY}/include")
	link_directories("${GLEW_DIRECTORY}/lib/${BINARY_DIRECTORY}")
endif(MSVC)

############
# Add GLEXT 

set(GL_VERSION "GL") 
set(GL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GL_VERSION})

###########
# Add GLM 

set(GLM_VERSION "glm-0.9.B.2")
set(GLM_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_VERSION})

include_directories("${GLM_DIRECTORY}")

###########
# Add GLI

set(GLI_VERSION "gli-0.2.1.0")
set(GLI_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/${GLI_VERSION})

include_directories("${GLI_DIRECTORY}")

################################
# Add libraries to executables

if(MSVC)
	set(BINARY_FILES "SDL" "SDLmain" "glew32s" "OpenGL32")
else(MSVC)
	set(BINARY_FILES "SDL" "SDLmain" "GL")
endif(MSVC)


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
	COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

set(OGL_DATA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

################################
# Add definitions

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS)

################################
# Add subdirectory

add_subdirectory(samples)
