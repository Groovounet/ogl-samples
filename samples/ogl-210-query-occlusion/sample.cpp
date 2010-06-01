//**********************************
// OpenGL occlusion query
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
	std::string const SAMPLE_NAME = "OpenGL occlusion query";	
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/flat-color.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 2;
	int const SAMPLE_MINOR_VERSION = 1;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

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
}//namespace

bool initQuery()
{
	glGenQueries(1, &QueryName);

	return glf::checkError("initQuery");
}

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		ProgramName = glf::createProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
		glBindAttribLocation(ProgramName, glf::semantic::attr::POSITION, "Position");
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformColor = glGetUniformLocation(ProgramName, "Diffuse");
	}

	// Set some variables 
	if(Validated)
	{
		// Bind the program for use
		glUseProgram(ProgramName);

		// Set uniform value
		glUniform4fv(UniformColor, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		// Unbind the program
		glUseProgram(0);
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

	// Reserve buffer memory but and copy the values
    glBufferData(GL_ARRAY_BUFFER, PositionSize, &PositionData[0][0], GL_STATIC_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool begin(glm::ivec2 const & WindowSize)
{
	WindowSize = WindowSize;

	bool Validated = true;
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initQuery();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, RotationCurrent.y, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, WindowSize.x, WindowSize.y);

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind program
	glUseProgram(ProgramName);

	// Set the value of MVP uniform.
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	// Beginning of the samples count query
	glBeginQuery(GL_SAMPLES_PASSED, QueryName);
	
	// Bind vertex attribute
	glBindBuffer(GL_ARRAY_BUFFER, BufferName);
	glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);

	// End of the samples count query
	glEndQuery(GL_SAMPLES_PASSED);

	// Get the count of samples. 
	// If the result of the query isn't here yet, we wait here...
	GLuint SamplesCount = 0;
	glGetQueryObjectuiv(QueryName, GL_QUERY_RESULT, &SamplesCount);
	fprintf(stdout, "Samples count: %d\r", SamplesCount);

	// Unbind program
	glUseProgram(0);

	glf::swapBuffers();
	glf::checkError("display");
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
