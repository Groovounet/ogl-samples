set(GL_VERSION "330")
set(NAME ogl-draw-elements-${GL_VERSION})

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../data/${GL_VERSION})

set(SHADER_VERT ${SHADER_DIR}/flat-color.vert)
set(SHADER_FRAG ${SHADER_DIR}/flat-color.frag)
set(SHADER_FILES ${SHADER_VERT} ${SHADER_FRAG})
set(SOURCE_FILES sample.hpp sample.cpp)

source_group(
	"Shader Files" 
	FILES 
	${SHADER_FILES})

add_executable(
	${NAME}
	${SOURCE_FILES} 
	${SHADER_FILES})

add_dependencies(
	${NAME} 
	${TARGET_DATA_COPY})

target_link_libraries(
	${NAME}
	${BINARY_FILES})
