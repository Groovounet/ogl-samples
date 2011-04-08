function(glCreateSampleGTC NAME)
	set(SAMPLE_NAME ogl-${GL_VERSION_GTC}-${NAME})
	set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../data/${GL_VERSION_GTC})

	foreach(FILE ${GL_SHADER_GTC})
 		set(SHADER_PATH ${SHADER_PATH} ${SHADER_DIR}/${FILE})
	endforeach(FILE)

	source_group("Shader Files" FILES ${SHADER_PATH})
	add_executable(${SAMPLE_NAME} ogl-${GL_VERSION_GTC}-${NAME} ${SHADER_PATH})
	add_dependencies(${SAMPLE_NAME} ${TARGET_DATA_COPY})
	target_link_libraries(${SAMPLE_NAME} ${BINARY_FILES})
endfunction(glCreateSampleGTC)

# OpenGL 2.1 samples
set(GL_VERSION_GTC 210)

set(GL_SHADER_GTC texture2d.vert texture2d.frag)
glCreateSampleGTC(texture2d)
glCreateSampleGTC(texture2d-compressed)

