cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(gli)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/glm-0.9.1.1")

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
# Add External package

addExternalPackageGTC("GLEW" "glew-1.5.8")
addExternalPackageGTC("FREEGLUT" "freeglut-2.6.0")
addExternalPackageGTC("GLM" "glm-0.9.1.1")

################################
# Add subdirectory

add_subdirectory(gli)
#add_subdirectory(doc)
#add_subdirectory(sample)
add_subdirectory(test)
