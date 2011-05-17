//**********************************
// OpenGL Primitive instancing
// 26/05/2010
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
	std::string const SAMPLE_NAME = "OpenGL Primitive instancing";	
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/primitive-instancing.vert");
	std::string const GEOM_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/primitive-instancing.geom");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/primitive-instancing.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(0);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 4;
	GLsizeiptr const VertexSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const VertexData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f)
	};

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace buffer
	{
		enum type
		{
			VERTEX,
			ELEMENT,
			MAX
		};
	}//namespace buffer

	GLuint ProgramName = 0;
	GLuint BufferName[buffer::MAX];
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
		GLuint VertShader = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE);
		GLuint GeomShader = glf::createShader(GL_GEOMETRY_SHADER, GEOM_SHADER_SOURCE);
		GLuint FragShader = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertShader);
		glAttachShader(ProgramName, GeomShader);
		glAttachShader(ProgramName, FragShader);
		glDeleteShader(VertShader);
		glDeleteShader(GeomShader);
		glDeleteShader(FragShader);

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

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initVertexBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool begin()
{
	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	glEnable(GL_DEPTH_TEST);

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
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glViewport(0, 0, Window.Size.x, Window.Size.y);

	float Depth(1.0f);
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f)[0]);

	glUseProgram(ProgramName);
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform4fv(UniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

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
