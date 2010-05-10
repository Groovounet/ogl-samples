set(NAME ogl-fbo-multiple-output)

set(SHADER_VERT1 ${CMAKE_CURRENT_SOURCE_DIR}/../../data/330/image-2d.vert)
set(SHADER_FRAG1 ${CMAKE_CURRENT_SOURCE_DIR}/../../data/330/image-2d.frag)
set(SHADER_VERT2 ${CMAKE_CURRENT_SOURCE_DIR}/../../data/330/multiple-output.vert)
set(SHADER_FRAG2 ${CMAKE_CURRENT_SOURCE_DIR}/../../data/330/multiple-output.frag)
set(SHADER_FILES ${SHADER_VERT1} ${SHADER_FRAG1} ${SHADER_VERT2} ${SHADER_FRAG2})
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
