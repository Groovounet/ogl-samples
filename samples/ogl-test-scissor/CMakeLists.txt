set(NAME ogl-test-scissor)

set(SHADER_VERT ../../data/image-2d.vert)
set(SHADER_FRAG ../../data/image-2d.frag)
set(IMAGE_FILE ../../data/kueken256-rgb8.dds)
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
