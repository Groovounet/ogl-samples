//**********************************
// OpenGL framebuffer multisample
// 01/09/2009
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
	std::string const SAMPLE_NAME = "OpenGL framebuffer multisample";	
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "image-2d.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "image-2d.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken320-rgb8.tga");
	glm::ivec2 const FRAMEBUFFER_SIZE(320, 240);

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
		vertex(glm::vec2(-4.0f,-3.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2( 4.0f,-3.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 4.0f, 3.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 4.0f, 3.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2(-4.0f, 3.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2(-4.0f,-3.0f), glm::vec2(0.0f, 1.0f))
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
		Validated = this->initProgram();
	if(Validated)
		Validated = this->initArrayBuffer();
	if(Validated)
		Validated = this->initVertexArray();
	if(Validated)
		Validated = this->initTexture2D();
	if(Validated)
		Validated = this->initFramebuffer();

	return Validated && glf::checkError("sample::begin");
}

bool sample::end()
{
	glDeleteBuffers(1, &this->BufferName);
	glDeleteProgram(this->ProgramName);
	glDeleteTextures(1, &this->Texture2DName);
	glDeleteTextures(1, &this->ColorTextureName);
	glDeleteRenderbuffers(1, &this->ColorRenderbufferName);
	glDeleteFramebuffers(1, &this->FramebufferRenderName);
	glDeleteFramebuffers(1, &this->FramebufferResolveName);
	glDeleteVertexArrays(1, &this->VertexArrayName);

	return glf::checkError("sample::end");
}

void sample::renderFBO(GLuint Framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 Perspective = glm::perspective(45.0f, float(FRAMEBUFFER_SIZE.x) / FRAMEBUFFER_SIZE.y, 0.1f, 100.0f);
	glm::mat4 ViewFlip = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,-1.0f, 1.0f));
	glm::mat4 ViewTranslate = glm::translate(ViewFlip, glm::vec3(0.0f, 0.0f, -TranlationCurrent.y * 2.0));
	glm::mat4 View = glm::rotate(ViewTranslate,-15.f, glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Perspective * View * Model;
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glViewport(0, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture2DName);

	glBindVertexArray(this->VertexArrayName);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glf::checkError("renderFBO");
}

void sample::renderFB(GLuint Texture2DName)
{
	glm::mat4 Perspective = glm::perspective(45.0f, float(this->WindowSize.x) / this->WindowSize.y, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -TranlationCurrent.y * 2.0));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, RotationCurrent.y, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Perspective * View * Model;
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture2DName);

	glBindVertexArray(this->VertexArrayName);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glf::checkError("renderFB");
}

void sample::render()
{
	// Clear the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->ProgramName);

	// Pass 1
	// Render the scene in a multisampled framebuffer
	glEnable(GL_MULTISAMPLE);
	renderFBO(this->FramebufferRenderName);
	glDisable(GL_MULTISAMPLE);

	// Resolved multisampling
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->FramebufferRenderName);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FramebufferResolveName);
	glBlitFramebuffer(
		0, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y, 
		0, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y, 
		GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Pass 2
	// Render the colorbuffer from the multisampled framebuffer
	glViewport(0, 0, this->WindowSize.x, this->WindowSize.y);
	renderFB(ColorTextureName);

	glf::checkError("sample::render");
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
		glUniform1i(this->UniformDiffuse, 0);

		// Unbind the program
		glUseProgram(0);
	}

	return glf::checkError("sample::initProgram");
}

bool sample::initArrayBuffer()
{
	glGenBuffers(1, &this->BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, this->BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("sample::initArrayBuffer");;
}

bool sample::initTexture2D()
{
	glGenTextures(1, &this->Texture2DName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture2DName);

	// Set filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
			GL_RGB, 
			GL_UNSIGNED_BYTE, 
			Image[Level].data());
	}

	return glf::checkError("initTexture2D");
}

bool sample::initFramebuffer()
{
	glGenRenderbuffers(1, &this->ColorRenderbufferName);
	glBindRenderbuffer(GL_RENDERBUFFER, this->ColorRenderbufferName);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	// The second parameter is the number of samples.

	glGenFramebuffers(1, &this->FramebufferRenderName);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FramebufferRenderName);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, ColorRenderbufferName);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenTextures(1, &this->ColorTextureName);
	glBindTexture(GL_TEXTURE_2D, this->ColorTextureName);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenFramebuffers(1, &this->FramebufferResolveName);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FramebufferResolveName);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTextureName, 0);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return glf::checkError("initFramebuffer");
}

bool sample::initVertexArray()
{
	// Create a dummy vertex array object where all the attribute buffers and element buffers would be attached 
	glGenVertexArrays(1, &this->VertexArrayName);
    glBindVertexArray(this->VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, this->BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
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

	fprintf(stdout, "OpenGL Error: this sample failed to run\n");

	delete Sample;
	Sample = 0;
	return 1;
}
