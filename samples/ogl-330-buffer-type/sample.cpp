//**********************************
// OpenGL buffer type
// 10/05/2010
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
	std::string const SAMPLE_NAME = "OpenGL buffer type";
	GLint const SAMPLE_MAJOR_VERSION = 2;
	GLint const SAMPLE_MINOR_VERSION = 1;
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/flat-color.frag");

	GLsizei const VertexCount = 6;
	GLsizeiptr const PositionSizeF64 = VertexCount * sizeof(glm::dvec2);
	glm::dvec2 const PositionDataF64[VertexCount] =
	{
		glm::dvec2(-1.0f, -1.0f),
		glm::dvec2( 1.0f, -1.0f),
		glm::dvec2( 1.0f,  1.0f),
		glm::dvec2( 1.0f,  1.0f),
		glm::dvec2(-1.0f,  1.0f),
		glm::dvec2(-1.0f, -1.0f)
	};

	GLsizeiptr const PositionSizeF32 = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionDataF32[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};

	GLsizeiptr const PositionSizeI8 = VertexCount * sizeof(glm::i8vec2);
	glm::i8vec2 const PositionDataI8[VertexCount] =
	{
		glm::i8vec2(-1,-1),
		glm::i8vec2( 1,-1),
		glm::i8vec2( 1, 1),
		glm::i8vec2( 1, 1),
		glm::i8vec2(-1, 1),
		glm::i8vec2(-1,-1)
	};

	GLsizeiptr const PositionSizeI32 = VertexCount * sizeof(glm::i32vec2);
	glm::i32vec2 const PositionDataI32[VertexCount] =
	{
		glm::i32vec2(-1,-1),
		glm::i32vec2( 1,-1),
		glm::i32vec2( 1, 1),
		glm::i32vec2( 1, 1),
		glm::i32vec2(-1, 1),
		glm::i32vec2(-1,-1)
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
	return glf::checkError("sample::check");
}

bool sample::begin(glm::ivec2 const & WindowSize)
{
	this->Viewport[BUFFER_F64] = glm::ivec4(0, 0, this->WindowSize >> 1);
	this->BufferType[BUFFER_F64] = GL_DOUBLE;
	this->Viewport[BUFFER_F32] = glm::ivec4(this->WindowSize.x >> 1, 0, this->WindowSize >> 1);
	this->BufferType[BUFFER_F32] = GL_FLOAT;
	this->Viewport[BUFFER_I8]  = glm::ivec4(this->WindowSize.x >> 1, this->WindowSize.y >> 1, this->WindowSize >> 1);
	this->BufferType[BUFFER_I8]  = GL_BYTE;
	this->Viewport[BUFFER_I32] = glm::ivec4(0, this->WindowSize.y >> 1, this->WindowSize >> 1);
	this->BufferType[BUFFER_I32] = GL_INT;

	bool Validated = true;
	if(Validated)
		Validated = this->initProgram();
	if(Validated)
		Validated = this->initArrayBuffer();

	return Validated && glf::checkError("sample::begin");
}

bool sample::end()
{
	// Delete objects
	glDeleteBuffers(BUFFER_MAX, this->BufferName);
	glDeleteProgram(this->ProgramName);

	return glf::checkError("sample::end");
}

void sample::render()
{
	// Compute the MVP (Model View Projection matrix)
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslateZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslateZ, RotationCurrent.y, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 View = ViewRotateY;
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind program
	glUseProgram(this->ProgramName);

	// Set the value of MVP uniform.
	glUniformMatrix4fv(this->UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	for(std::size_t Index = 0; Index < BUFFER_MAX; ++Index)
	{
		// Set the display viewport
		glViewport(
			this->Viewport[Index].x, 
			this->Viewport[Index].y, 
			this->Viewport[Index].z, 
			this->Viewport[Index].w);

		// Bind vertex attribute
		glBindBuffer(GL_ARRAY_BUFFER, this->BufferName[Index]);
			glVertexAttribPointer(glf::semantic::attr::POSITION, 2, this->BufferType[Index], GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Draw
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
			glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glDisableVertexAttribArray(glf::semantic::attr::POSITION);
	}

	// Unbind program
	glUseProgram(0);

	glf::checkError("sample::render");
}

bool sample::initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		this->ProgramName = glf::createProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
		glBindAttribLocation(this->ProgramName, glf::semantic::attr::POSITION, "Position");
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
	// Generate a buffer object
	glGenBuffers(BUFFER_MAX, this->BufferName);

	// Allocate and copy buffers memory
    glBindBuffer(GL_ARRAY_BUFFER, this->BufferName[BUFFER_F64]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeF64, PositionDataF64, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->BufferName[BUFFER_F32]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeF32, PositionDataF32, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->BufferName[BUFFER_I8]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeI8, PositionDataI8, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->BufferName[BUFFER_I32]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeI32, PositionDataI32, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("sample::initArrayBuffer");
}

int main(int argc, char* argv[])
{
	glm::ivec2 ScreenSize = glm::ivec2(640, 480);

	sample* Sample = new sample(
		SAMPLE_NAME, 
		ScreenSize, 
		SAMPLE_MAJOR_VERSION,
		SAMPLE_MINOR_VERSION);

	if(Sample->check())
	{
		Sample->begin(ScreenSize);
		Sample->run();
		Sample->end();

		delete Sample;
		Sample = 0;
		return 0;
	}

	fprintf(stderr, "OpenGL Error: this sample failed to run\n");

	delete Sample;
	Sample = 0;
	return 1;
}
