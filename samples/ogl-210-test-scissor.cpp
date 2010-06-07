//**********************************
// OpenGL Test scissor
// 10/05/2010
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
	std::string const SAMPLE_NAME = "OpenGL Test scissor";	
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/image-2d.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "210/image-2d.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken256-rgb8.dds");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 2;
	int const SAMPLE_MINOR_VERSION = 1;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	struct vertex
	{
		vertex
		(
			glm::vec2 const & Position,
			glm::vec2 const & Texcoord
		) :
			Position(Position),
			Texcoord(Texcoord)
		{}

		glm::vec2 Position;
		glm::vec2 Texcoord;
	};

	// With DDS textures, v texture coordinate are reversed, from top to bottom
	GLsizei const VertexCount = 6;
	GLsizeiptr const VertexSize = VertexCount * sizeof(vertex);
	vertex const VertexData[VertexCount] =
	{
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f))
	};

	GLuint VertexArrayName = 0;
	GLuint ProgramName = 0;

	GLuint BufferName = 0;
	GLuint Texture2DName = 0;

	GLuint UniformMVP = 0;
	GLuint UniformDiffuse = 0;
}//namespace

bool initProgram()
{
	bool Validated = true;
	
	{
		::ProgramName = glf::createProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
		glBindAttribLocation(::ProgramName, glf::semantic::attr::POSITION, "Position");
		glLinkProgram(::ProgramName);
		Validated = glf::checkProgram(::ProgramName);
	}

	if(Validated)
	{
		::UniformMVP = glGetUniformLocation(::ProgramName, "MVP");
		::UniformDiffuse = glGetUniformLocation(::ProgramName, "Diffuse");
	}

	return glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &::BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, ::BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");;
}

bool initTexture2D()
{
	glGenTextures(1, &::Texture2DName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ::Texture2DName);

	// Set filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set image
	gli::image Image = gli::import_as(TEXTURE_DIFFUSE);
	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGB, 
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0,  
			GL_BGR, 
			GL_UNSIGNED_BYTE, 
			Image[Level].data());
	}

	return glf::checkError("initTexture2D");
}

bool begin()
{
	bool Validated = true;
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initTexture2D();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(1, &::BufferName);
	glDeleteProgram(::ProgramName);
	glDeleteTextures(1, &::Texture2DName);

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

	glViewport(0, 0, ::Window.Size.x, ::Window.Size.y);
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::vec3 MinScissor( 10000.f);
	glm::vec3 MaxScissor(-10000.f);

	glm::mat4 Ortho = glm::ortho(0.0f, 0.0f, 640.f, 480.0f);
	for(GLsizei i = 0; i < VertexCount; ++i)
	{
		glm::vec3 Projected = glm::project(
			glm::vec3(VertexData[i].Position, 0.0f), 
			View * Model, 
			Projection, 
			glm::ivec4(0, 0, ::Window.Size.x, ::Window.Size.y));

		MinScissor = glm::min(MinScissor, glm::vec3(Projected));
		MaxScissor = glm::max(MaxScissor, glm::vec3(Projected));
	}

	glScissor(GLint(MinScissor.x), GLint(MinScissor.y), GLsizei(MaxScissor.x - MinScissor.x), GLsizei(MaxScissor.y - MinScissor.y));
	glEnable(GL_SCISSOR_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the program for use
	glUseProgram(::ProgramName);

	glUniform1i(::UniformDiffuse, 0);
	glUniformMatrix4fv(::UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ::Texture2DName);

	glBindBuffer(GL_ARRAY_BUFFER, ::BufferName);
	glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
	glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
		glDrawArrays(GL_TRIANGLES, 0, VertexCount);
	glDisableVertexAttribArray(glf::semantic::attr::POSITION);
	glDisableVertexAttribArray(glf::semantic::attr::TEXCOORD);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_SCISSOR_TEST);

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