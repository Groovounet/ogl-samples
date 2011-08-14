//**********************************
// OpenGL Samples Pack 
// ogl-samples.g-truc.net
//**********************************
// OpenGL Uniform Buffer Shared
// 06/04/2010
//**********************************
// Christophe Riccio
// ogl-samples@g-truc.net
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Uniform Buffer";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "420/buffer-uniform.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "420/buffer-uniform.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(4);
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f)
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	GLuint const Instances(2);

	GLuint ProgramName(0);
	GLuint ElementBufferName(0);
	GLuint ArrayBufferName(0);
	GLuint VertexArrayName(0);
	GLuint TransformBufferName(0);
	GLuint MaterialBufferName(0);
	GLint UniformBufferOffset(0);
}//namespace

bool initProgram()
{
	bool Validated(true);
	
	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertShaderName);
		glAttachShader(ProgramName, FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		glLinkProgram(ProgramName);
		Validated = Validated && glf::checkProgram(ProgramName);
	}

	return Validated;
}

bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return Validated;
}

bool initArrayBuffer()
{
	bool Validated(true);

	glGenBuffers(1, &ElementBufferName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferName);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return Validated;
}

bool initUniformBuffer()
{
	bool Validated(true);

	GLint UniformBlockSize(0);

	glGetActiveUniformBlockiv(
		ProgramName, 
		glf::semantic::uniform::TRANSFORM0,
		GL_UNIFORM_BLOCK_DATA_SIZE,
		&UniformBlockSize);
	UniformBlockSize = ((UniformBlockSize / UniformBufferOffset) + 1) * UniformBufferOffset;

	glGenBuffers(1, &TransformBufferName);
	glBindBuffer(GL_UNIFORM_BUFFER, TransformBufferName);
	glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize * Instances, 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Attach the buffer to UBO binding point glf::semantic::uniform::TRANSFORM0
	glBindBufferRange(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, TransformBufferName, 0, UniformBlockSize);
	// Attach the buffer to UBO binding point glf::semantic::uniform::TRANSFORM1
	glBindBufferRange(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM1, TransformBufferName, UniformBlockSize, UniformBlockSize);

	{
		glm::vec4 Diffuse(1.0f, 0.5f, 0.0f, 1.0f);

		glGetActiveUniformBlockiv(
			ProgramName, 
			glf::semantic::uniform::MATERIAL,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&UniformBlockSize);

		glGenBuffers(1, &MaterialBufferName);
		glBindBuffer(GL_UNIFORM_BUFFER, MaterialBufferName);
		glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize, &Diffuse[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Attach the buffer to UBO binding point glf::semantic::uniform::MATERIAL
		glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::MATERIAL, MaterialBufferName);
	}

	return Validated;
}

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool begin()
{
	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	glGetIntegerv(
		GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
		&UniformBufferOffset);

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initUniformBuffer();

	return Validated;
}

bool end()
{
	bool Validated(true);

	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteBuffers(1, &ArrayBufferName);
	glDeleteBuffers(1, &ElementBufferName);
	glDeleteBuffers(1, &TransformBufferName);
	glDeleteBuffers(1, &MaterialBufferName);
	glDeleteProgram(ProgramName);

	return Validated;
}

void display()
{
	{
		// Compute the MVP (Model View Projection matrix)
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y + 45.0f, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x + 45.0f, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glBindBuffer(GL_UNIFORM_BUFFER, TransformBufferName);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(MVP), &MVP[0][0]);
	}
	{
		// Compute the MVP (Model View Projection matrix)
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y + 45.0f, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x + 90.f + 45.0f, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glBindBuffer(GL_UNIFORM_BUFFER, TransformBufferName);
		glBufferSubData(GL_UNIFORM_BUFFER, UniformBufferOffset, sizeof(MVP), &MVP[0][0]);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glViewport(0, 0, Window.Size.x, Window.Size.y);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

	glUseProgram(ProgramName);

	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferName);
	glDrawElementsInstancedBaseVertexBaseInstance(
		GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, 0, 2, 0, 0);

	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT), 
		::SAMPLE_MAJOR_VERSION, 
		::SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}
