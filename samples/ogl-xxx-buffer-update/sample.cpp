//**********************************
// OpenGL Buffer Update
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
	std::string const SAMPLE_NAME = "OpenGL Buffer Update";
        std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "xxx/flat-color.vert");
        std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "xxx/flat-color.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
        int const SAMPLE_MAJOR_VERSION = 4;
        int const SAMPLE_MINOR_VERSION = 0;

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

	GLuint VertexArrayName = 0;
	GLuint ProgramName = 0;
	GLuint BufferName = 0;
	GLint UniformMVP = 0;
	GLint UniformColor = 0;	

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
		UniformColor = glGetUniformLocation(ProgramName, "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

// Buffer update using glMapNamedBufferRange
bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &BufferName);

	// Reserve buffer memory but don't copy the values
    glNamedBufferDataEXT(
                BufferName,
		PositionSize, 
		0, 
		GL_STATIC_DRAW);

	// Copy the vertex data in the buffer, in this sample for the whole range of data.
	// It doesn't required to be the buffer size but pointers require no memory overlapping.
    GLvoid* Data = glMapNamedBufferRangeEXT(
                BufferName,
		0,				// Offset
		PositionSize,	// Size,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);
	memcpy(Data, PositionData, PositionSize);

	// Explicitly send the data to the graphic card.
        glFlushMappedNamedBufferRangeEXT(BufferName, 0, PositionSize);

        glUnmapNamedBufferEXT(BufferName);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
        glGenVertexArrays(1, &VertexArrayName);

        glVertexArrayVertexAttribOffsetEXT(VertexArrayName, ArrayBufferName, glf::semantic::attr::POSITION, 2, GL_HALF_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);

        // DSA function missing...
    glBindVertexArray(VertexArrayName);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferName);
        glBindVertexArray(0);

        return glf::checkError("initVertexArray");
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
	// Delete objects
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

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
        glProgramUniform4fvEXT(ProgramName, UniformColor, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	// Set the display viewport
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

        // Bind program
        glUseProgram(ProgramName);

	glBindVertexArray(VertexArrayName);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);

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
