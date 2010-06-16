//**********************************
// OpenGL Vertex Array
// 07/06/2009
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
	std::string const SAMPLE_NAME = "OpenGL Vertex array";	
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "xxx/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "xxx/flat-color.frag");
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
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLubyte);
	GLubyte const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	GLuint ProgramName = 0;
	GLuint ElementBufferName = 0;
	GLuint ArrayBufferName = 0;
	GLuint VertexArrayName = 0;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		ProgramName = glf::createProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	// Set some variables 
	if(Validated)
	{
		// Set uniform value
		glProgramUniform4fvEXT(ProgramName, UniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	// Build a vertex array object
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, ArrayBufferName, glf::semantic::attr::POSITION, 2, GL_HALF_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);

    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferName);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &ElementBufferName);
    glNamedBufferDataEXT(ElementBufferName, ElementSize, ElementData, GL_STATIC_DRAW);

	glGenBuffers(1, &ArrayBufferName);
    glNamedBufferDataEXT(ArrayBufferName, PositionSize, PositionData, GL_STATIC_DRAW);

	return glf::checkError("initArrayBuffer");
}

bool begin()
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Validated = (MajorVersion * 10 + MinorVersion) >= (SAMPLE_MAJOR_VERSION * 10 + SAMPLE_MINOR_VERSION);

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteBuffers(1, &ArrayBufferName);
	glDeleteBuffers(1, &ElementBufferName);
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

	// Set the value of MVP uniform.
	glProgramUniformMatrix4fvEXT(ProgramName, UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	// Set the display viewport
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	// Clear color buffer with black
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

	// Bind program
	glUseProgram(ProgramName);

	// Bind vertex array & draw 
	glBindVertexArray(VertexArrayName);
		glDrawElements(GL_TRIANGLES, ElementCount, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);

	// Unbind program
	glUseProgram(0);

	glf::checkError("display");
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
