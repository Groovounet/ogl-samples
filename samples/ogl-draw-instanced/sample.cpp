//**********************************
// OpenGL draw instanced
// 26/08/2009
//**********************************
// Christophe Riccio
// g.truc.creation@gmail.com
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include "sample.hpp"

namespace
{
	std::string const SAMPLE_NAME = "OpenGL draw instanced";
	GLint const SAMPLE_MAJOR_VERSION = 3;
	GLint const SAMPLE_MINOR_VERSION = 3;
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/instanced.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/instanced.frag");

	GLsizei const VertexCount = 6;
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};
}

sample::sample
(
	std::string const & Name, 
	glm::ivec2 const & WindowSize,
	glm::uint32 VersionMajor,
	glm::uint32 VersionMinor
) :
	window(Name, WindowSize, VersionMajor, VersionMinor),
	ProgramName(0)
{}

sample::~sample()
{}

bool sample::check() const
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Version = (MajorVersion * 10 + MinorVersion) >= (glf::SAMPLE_MAJOR * 10 + glf::SAMPLE_MINOR);
	return Version && glf::checkError("sample::check");
}

bool sample::begin(glm::ivec2 const & WindowSize)
{
	this->WindowSize = WindowSize;

	bool Validated = true;
	if(Validated)
		Validated = this->initTest();
	if(Validated)
		Validated = this->initProgram();
	if(Validated)
		Validated = this->initArrayBuffer();
	if(Validated)
		Validated = this->initVertexArray();

	return Validated && glf::checkError("sample::begin");
}

bool sample::end()
{
	// Delete objects
	glDeleteBuffers(1, &this->BufferName);
	glDeleteProgram(this->ProgramName);
	glDeleteVertexArrays(1, &this->VertexArrayName);

	return glf::checkError("sample::end");
}

void sample::render()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, RotationCurrent.y, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, this->WindowSize.x, this->WindowSize.y);

	// Clear color buffer with black
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind program
	glUseProgram(this->ProgramName);

	// Set the value of MVP uniform.
	glUniformMatrix4fv(this->UniformMVP, 1, GL_FALSE, &MVP[0][0]);

    glBindVertexArray(this->VertexArrayName);
	glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 5);

	// Unbind program
	glUseProgram(0);

	glf::checkError("sample::render");
}

bool sample::initTest()
{
	bool Validated = true;
	glEnable(GL_DEPTH_TEST);

	return Validated && glf::checkError("sample::initTest");
}

bool sample::initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		this->ProgramName = glf::createProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
		glLinkProgram(this->ProgramName);
		Validated = glf::checkProgram(this->ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		this->UniformMVP = glGetUniformLocation(this->ProgramName, "MVP");
		this->UniformDiffuse = glGetUniformLocation(this->ProgramName, "Diffuse");
	}

	// Set some variables 
	if(Validated)
	{
		// Bind the program for use
		glUseProgram(this->ProgramName);

		// Set uniform value
		glUniform4fv(this->UniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		// Unbind the program
		glUseProgram(0);
	}

	return Validated && glf::checkError("sample::initProgram");
}

bool sample::initArrayBuffer()
{
	glGenBuffers(1, &this->BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, this->BufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("sample::initArrayBuffer");
}

bool sample::initVertexArray()
{
	// Create a dummy vertex array object where all the attribute buffers and element buffers would be attached 
	glGenVertexArrays(1, &this->VertexArrayName);
    glBindVertexArray(this->VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, this->BufferName);
			glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return glf::checkError("sample::initVertexArray");
}

int main(int argc, char* argv[])
{
	glm::ivec2 ScreenSize = glm::ivec2(640, 480);

	sample* Sample = new sample(
		SAMPLE_NAME, 
		ScreenSize, 
		glf::SAMPLE_MAJOR,
		glf::SAMPLE_MINOR);

	if(Sample->check())
	{
		Sample->begin(ScreenSize);
		Sample->run();
		Sample->end();

		delete Sample;
		return 0;
	}

	fprintf(stderr, "OpenGL Error: this sample failed to run\n");

	delete Sample;
	Sample = 0;
	return 1;
}
