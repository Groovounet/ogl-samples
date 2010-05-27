set(GL_VERSION "400")
set(NAME ogl-${GL_VERSION}-primitive-tessellation)

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../data/${GL_VERSION})

set(SHADER_VERT ${SHADER_DIR}/tess.vert)
set(SHADER_CONT ${SHADER_DIR}/tess.cont)
set(SHADER_EVAL ${SHADER_DIR}/tess.eval)
set(SHADER_FRAG ${SHADER_DIR}/tess.frag)
set(SHADER_FILES ${SHADER_VERT} ${SHADER_CONT} ${SHADER_EVAL} ${SHADER_FRAG})
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
