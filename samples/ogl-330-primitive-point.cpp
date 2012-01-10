//**********************************
// OpenGL Samples Pack
// ogl-samples.g-truc.net
//**********************************
// OpenGL Point
// 24/09/2011 - 24/09/2011
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
	std::string const SAMPLE_NAME = "OpenGL Point";
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/point.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/point.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(3);
	int const SAMPLE_MINOR_VERSION(3);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	std::size_t const VertexCount(4000);

	GLuint VertexArrayName(0);
	GLuint ProgramName(0);
	GLuint BufferName(0);
	GLint UniformMVP(0);
	GLint UniformMV(0);
}//namespace

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertShaderName);
		glAttachShader(ProgramName, FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformMV = glGetUniformLocation(ProgramName, "MV");
	}

	return Validated && glf::checkError("initProgram");
}

// Buffer update using glBufferSubData
bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &BufferName);

	// Bind the buffer for use
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);

	// Reserve buffer memory but don't copy the values
    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(VertexCount * sizeof(glf::vertex_v4fc4f)), NULL, GL_STATIC_DRAW);

    glf::vertex_v4fc4f* Data = (glf::vertex_v4fc4f*)glMapBufferRange(
		GL_ARRAY_BUFFER, 
		0,				// Offset
		GLsizeiptr(VertexCount * sizeof(glf::vertex_v4fc4f)),	// Size,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);

	for(std::size_t i = 0; i < VertexCount; ++i)
	{
		//Data[i].Position = glm::vec4(glm::linearRand(glm::vec2(-1), glm::vec2(1)), glm::gaussRand(0.0f, 1.0f), 1);
		//Data[i].Position = glm::vec4(glm::linearRand(glm::vec2(-1), glm::vec2(1)), /*glm::gaussRand(0.0f, 1.0f)*/0, 1);
		//Data[i].Position = glm::vec4(glm::sphericalRand(1.0f), 1);
		Data[i].Position = glm::vec4(glm::gaussRand(glm::vec3(0), glm::vec3(1)), 1);
		//Data[i].Position = glm::vec4(glm::circularRand(1.0f), 0, 1);
		//Data[i].Position = glm::vec4(glm::diskRand(1.0f), 0, 1);
		//Data[i].Position = glm::vec4(glm::ballRand(1.0f), 1);
		Data[i].Color = glm::vec4(1);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fc4f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fc4f), GLF_BUFFER_OFFSET(sizeof(glm::vec4)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_ARB_viewport_array");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_PROGRAM_POINT_SIZE);
	//glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
	
	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
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
	// Delete objects
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

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
	glm::mat4 MV = View * Model;

	glProgramUniformMatrix4fv(ProgramName, UniformMV, 1, GL_FALSE, &MV[0][0]);
	glProgramUniformMatrix4fv(ProgramName, UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	float Depth(1.0f);
	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);
	glClearBufferfv(GL_DEPTH, 0, &Depth);

	glDisable(GL_SCISSOR_TEST);

	glUseProgram(ProgramName);

	glBindVertexArray(VertexArrayName);

	glDrawArraysInstanced(GL_POINTS, 0, VertexCount, 1);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	return glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT), 
		::SAMPLE_MAJOR_VERSION, 
		::SAMPLE_MINOR_VERSION);
}
