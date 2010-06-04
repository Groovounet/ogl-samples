//**********************************
// OpenGL Buffer Texture
// 04/06/2010
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
	std::string const SAMPLE_NAME = "OpenGL Buffer Texture";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/texture-buffer.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/texture-buffer.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 3;
	int const SAMPLE_MINOR_VERSION = 3;

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
	GLuint DisplacementBufferName = 0;
	GLuint DisplacementTextureName = 0;
	GLuint DiffuseBufferName = 0;
	GLuint DiffuseTextureName = 0;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;
	GLint UniformDisplacement = 0;
	
}//namespace

bool initTest()
{
	bool Validated = true;
	glEnable(GL_DEPTH_TEST);

	return Validated && glf::checkError("initTest");
}

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
		UniformDisplacement = glGetUniformLocation(ProgramName, "Displacement");
	}

	return Validated && glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initTextureBuffer()
{
	glm::vec4 Displacement[5] = 
	{
		glm::vec4( 0.1f, 0.3f,-1.0f, 0.0f), 
		glm::vec4(-0.5f, 0.0f,-0.5f, 0.0f),
		glm::vec4(-0.2f,-0.2f, 0.0f, 0.0f),
		glm::vec4( 0.3f, 0.2f, 0.5f, 0.0f),
		glm::vec4( 0.1f,-0.3f, 1.0f, 0.0f)
	};

	glGenBuffers(1, &DisplacementBufferName);
    glBindBuffer(GL_TEXTURE_BUFFER, DisplacementBufferName);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(Displacement), Displacement, GL_STATIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	glGenTextures(1, &DisplacementTextureName);
	glBindTexture(GL_TEXTURE_BUFFER, DisplacementTextureName);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, DisplacementBufferName);
	glBindTexture(GL_TEXTURE_BUFFER, 0);

	glm::u8vec4 Diffuse[5] = 
	{
		glm::u8vec4(255,   0,   0, 255), 
		glm::u8vec4(255, 127,   0, 255),
		glm::u8vec4(255, 255,   0, 255),
		glm::u8vec4(  0, 255,   0, 255),
		glm::u8vec4(  0,   0, 255, 255)
	};	

	glGenBuffers(1, &DiffuseBufferName);
    glBindBuffer(GL_TEXTURE_BUFFER, DiffuseBufferName);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(Diffuse), Diffuse, GL_STATIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	glGenTextures(1, &DiffuseTextureName);
	glBindTexture(GL_TEXTURE_BUFFER, DiffuseTextureName);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8, DiffuseTextureName);
	glBindTexture(GL_TEXTURE_BUFFER, 0);	

	return glf::checkError("initTextureBuffer");
}

bool initVertexArray()
{
	// Create a dummy vertex array object where all the attribute buffers and element buffers would be attached 
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
			glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
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
		Validated = initTest();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initTextureBuffer();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteTextures(1, &DiffuseTextureName);
	glDeleteBuffers(1, &DiffuseBufferName);
	glDeleteTextures(1, &DisplacementTextureName);
	glDeleteBuffers(1, &DisplacementBufferName);
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

	// Set the display viewport
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	// Clear color buffer with black
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind program
	glUseProgram(ProgramName);

	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(UniformDisplacement, 0);
	glUniform1i(UniformDiffuse, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER, DisplacementTextureName);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_BUFFER, DiffuseTextureName);

    glBindVertexArray(VertexArrayName);
	glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 5);
	
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
