//**********************************
// OpenGL Double
// 30/06/2010 - 30/06/2010
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
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "4XX/double.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "4XX/double.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 0;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 6;

	GLsizeiptr const PositionSizeF64 = VertexCount * sizeof(glm::dvec2);
	glm::dvec2 const PositionDataF64[VertexCount] =
	{
		glm::dvec2(-1.0,-1.0),
		glm::dvec2( 1.0,-1.0),
		glm::dvec2( 1.0, 1.0),
		glm::dvec2(-1.0, 1.0)
	};

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace program
	{
		enum type
		{
			VERTEX,
			FRAGMENT,
			MAX
		};
	}//namespace program

	namespace buffer
	{
		enum type
		{
			F64,
			ELEMENT,
			MAX
		};
	}//namespace buffer

	GLuint ProgramName[program::MAX];
	GLuint BufferName[buffer::MAX];
	GLuint VertexArrayName;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	if(Validated)
	{
		std::string VertexSource = glf::loadFile(VERTEX_SHADER_SOURCE);
		ProgramName[program::VERTEX] = glCreateShaderProgramEXT(GL_VERTEX_SHADER, VertexSource.c_str());
		Validated = glf::checkProgram(ProgramName[program::VERTEX]);
	}

	if(Validated)
	{
		std::string FragmentSource = glf::loadFile(FRAGMENT_SHADER_SOURCE);
		ProgramName[program::FRAGMENT] = glCreateShaderProgramEXT(GL_FRAGMENT_SHADER, FragmentSource.c_str());
		Validated = glf::checkProgram(ProgramName[program::FRAGMENT]);
	}

	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName[program::VERTEX], "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName[program::FRAGMENT], "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);
	glNamedBufferDataEXT(BufferName[buffer::F64], PositionSizeF64, PositionDataF64, GL_STATIC_DRAW);
	glNamedBufferDataEXT(BufferName[buffer::ELEMENT], ElementSize, ElementData, GL_STATIC_DRAW);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
	glVertexArrayVertexAttribLOffsetEXT(VertexArrayName, BufferName[buffer::F64], glf::semantic::attr::POSITION, 2, GL_FLOAT, sizeof(glm::dvec2), 0);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Validated = glf::version(MajorVersion, MinorVersion) >= glf::version(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && GLEW_EXT_direct_state_access;
	Validated = Validated && GLEW_EXT_direct_state_access_memory;
	Validated = Validated && GLEW_EXT_vertex_attrib_64bit;
	Validated = Validated && GLEW_EXT_separate_shader_objects;
	 
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
	glDeleteProgram(ProgramName[program::VERTEX]);
	glDeleteProgram(ProgramName[program::FRAGMENT]);

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

	glProgramUniformMatrix4dvEXT(ProgramName[program::VERTEX], UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform4dvEXT(ProgramName[program::FRAGMENT], UniformDiffuse, 1, &glm::dvec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glViewport(0, 0, Window.Size.x, Window.Size.y);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glUseShaderProgramEXT(GL_VERTEX_SHADER, ProgramName[program::VERTEX]);
	glUseShaderProgramEXT(GL_FRAGMENT_SHADER, ProgramName[program::FRAGMENT]);
	
	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);

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
