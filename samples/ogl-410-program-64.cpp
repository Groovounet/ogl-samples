//**********************************
// OpenGL Double
// 02/08/2010 - 02/08/2010
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
	std::string const SAMPLE_NAME = "OpenGL Double";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/double.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/double.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 1;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(glm::uint16);
	glm::uint16 const ElementData[ElementCount] =
	{
		0, 1, 2,
		0, 2, 3
	};

	GLsizei const VertexCount = 4;
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::dvec2);
	glm::dvec2 const PositionData[VertexCount] =
	{
		glm::dvec2(-1.0f,-1.0f),
		glm::dvec2( 1.0f,-1.0f),
		glm::dvec2( 1.0f, 1.0f),
		glm::dvec2(-1.0f, 1.0f)
	};

	namespace buffer
	{
		enum type
		{
			F64,
			ELEMENT,
			MAX
		};
	}//namespace buffer

	GLuint ProgramName = 0;
	GLuint BufferName[buffer::MAX];
	GLuint VertexArrayName;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertexShaderName);
		glAttachShader(ProgramName, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexBuffer()
{
	// Generate a buffer object
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F64]);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F64]);
		glVertexAttribLPointer(glf::semantic::attr::POSITION, 2, GL_DOUBLE, sizeof(glm::dvec2), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Validated = glf::version(MajorVersion, MinorVersion) >= glf::version(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initVertexBuffer();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
    glm::dmat4 Projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
	glm::dmat4 ViewTranslateZ = glm::translate(glm::dmat4(1.0), glm::dvec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::dmat4 ViewRotateX = glm::rotate(ViewTranslateZ, double(Window.RotationCurrent.y), glm::dvec3(1.f, 0.f, 0.f));
	glm::dmat4 ViewRotateY = glm::rotate(ViewRotateX, double(Window.RotationCurrent.x), glm::dvec3(0.f, 1.f, 0.f));
	glm::dmat4 View = ViewRotateY;
	glm::dmat4 Model = glm::dmat4(1.0f);
	glm::dmat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	// Clear color buffer with black
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	// Bind program
	glUseProgram(ProgramName);

	glUniformMatrix4dv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform4dv(UniformDiffuse, 1, &glm::dvec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glBindVertexArray(VertexArrayName);
	glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1, 0);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT), 
		SAMPLE_MAJOR_VERSION, 
		SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}
