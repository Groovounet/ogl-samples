//**********************************
// OpenGL Uniform Buffer
// 07/06/2010
//**********************************
// Christophe Riccio
// g.truc.creation@gmail.com
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Uniform Buffer";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "4XX/uniform-buffer.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "4XX/uniform-buffer.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 0;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 4;
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::hvec2);
	glm::hvec2 const PositionData[VertexCount] =
	{
		glm::hvec2(-1.0f,-1.0f),
		glm::hvec2( 1.0f,-1.0f),
		glm::hvec2( 1.0f, 1.0f),
		glm::hvec2(-1.0f, 1.0f)
	};

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLuint ProgramName = 0;
	GLuint ElementBufferName = 0;
	GLuint ArrayBufferName = 0;
	GLuint VertexArrayName = 0;
	GLuint TransformBufferName = 0;
	GLuint MaterialBufferName = 0;
	GLint UniformTransform = 0;
	GLint UniformMaterial = 0;

}//namespace

bool initProgram()
{
	bool Validated = true;

	// Create program
	if(Validated)
	{
		ProgramName = glCreateProgram();
		GLuint VertexShader = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		glAttachShader(ProgramName, VertexShader);
		glDeleteShader(VertexShader);
		GLuint FragmentShader = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);
		glAttachShader(ProgramName, FragmentShader);
		glDeleteShader(FragmentShader);
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMaterial = glGetUniformBlockIndex(ProgramName, "material");
		UniformTransform = glGetUniformBlockIndex(ProgramName, "transform");

		// Associate the uniform blocks to their indices.
		glUniformBlockBinding(ProgramName, UniformTransform, glf::semantic::uniform::TRANSFORM);
		glUniformBlockBinding(ProgramName, UniformMaterial, glf::semantic::uniform::MATERIAL);
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, ArrayBufferName, glf::semantic::attr::POSITION, 2, GL_HALF_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);

	return glf::checkError("initVertexArray");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &ElementBufferName);
    glNamedBufferDataEXT(ElementBufferName, ElementSize, ElementData, GL_STATIC_DRAW);

	glGenBuffers(1, &ArrayBufferName);
    glNamedBufferDataEXT(ArrayBufferName, PositionSize, PositionData, GL_STATIC_DRAW);

	void * Data = glMapNamedBufferRangeEXT(
		ArrayBufferName, 0, PositionSize, 
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);
	memcpy(Data, &PositionData[0], PositionSize);
	glFlushMappedNamedBufferRangeEXT(ArrayBufferName, 0, PositionSize);
	glUnmapNamedBufferEXT(ArrayBufferName);

	return glf::checkError("initArrayBuffer");
}

bool initUniformBuffer()
{
	GLint UniformBlockSize = 0;

	glGetActiveUniformBlockiv(
		ProgramName,
		UniformTransform,
		GL_UNIFORM_BLOCK_DATA_SIZE,
		&UniformBlockSize);
	glGenBuffers(1, &TransformBufferName);
	glNamedBufferDataEXT(TransformBufferName, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);

	glm::vec4 Diffuse(1.0f, 0.5f, 0.0f, 1.0f);
	glGetActiveUniformBlockiv(
		ProgramName,
		UniformMaterial,
		GL_UNIFORM_BLOCK_DATA_SIZE,
		&UniformBlockSize);
	glGenBuffers(1, &MaterialBufferName);
	glNamedBufferDataEXT(MaterialBufferName, UniformBlockSize, &Diffuse[0], GL_DYNAMIC_DRAW);

	return glf::checkError("initUniformBuffer");
}

bool begin()
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Validated = (MajorVersion * 10 + MinorVersion) >= (SAMPLE_MAJOR_VERSION * 10 + SAMPLE_MINOR_VERSION);
	Validated = Validated && GLEW_EXT_direct_state_access;

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initUniformBuffer();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteBuffers(1, &ArrayBufferName);
	glDeleteBuffers(1, &ElementBufferName);
	glDeleteBuffers(1, &TransformBufferName);
	glDeleteBuffers(1, &MaterialBufferName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glNamedBufferSubDataEXT(TransformBufferName, 0, sizeof(MVP), &MVP[0][0]);

	// Attach the buffer to UBO binding point glf::semantic::uniform::TRANSFORM
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM, TransformBufferName);

	// Attach the buffer to UBO binding point glf::semantic::uniform::MATERIAL
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::MATERIAL, MaterialBufferName);

	// Set the display viewport
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	// Clear color buffer
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

	// Bind program
	glUseProgram(ProgramName);

	// Bind vertex array & draw
	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferName);

	glDrawElementsInstanced(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT),
		SAMPLE_MAJOR_VERSION,
		SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}
