set(NAME ogl-transform-feedback-object)

set(SHADER_VERT ${CMAKE_CURRENT_SOURCE_DIR}/../../data/400/flat-color.vert ${CMAKE_CURRENT_SOURCE_DIR}/../../data/400/transformed.vert)
set(SHADER_FRAG ${CMAKE_CURRENT_SOURCE_DIR}/../../data/400/flat-color.frag ${CMAKE_CURRENT_SOURCE_DIR}/../../data/400/transformed.frag)
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
