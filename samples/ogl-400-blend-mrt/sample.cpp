//**********************************
// OpenGL Blend MRT
// 28/05/2010
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
	std::string const SAMPLE_NAME = "OpenGL Blend MRT";
	GLint const SAMPLE_MAJOR_VERSION = 3;
	GLint const SAMPLE_MINOR_VERSION = 3;
	std::string const VERTEX_SHADER_SOURCE1(glf::DATA_DIRECTORY + "400/mrt.vert");
	std::string const FRAGMENT_SHADER_SOURCE1(glf::DATA_DIRECTORY + "400/mrt.frag");
	std::string const VERTEX_SHADER_SOURCE2(glf::DATA_DIRECTORY + "400/image-2d.vert");
	std::string const FRAGMENT_SHADER_SOURCE2(glf::DATA_DIRECTORY + "400/image-2d.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken320-rgb8.tga");
	glm::ivec2 const FRAMEBUFFER_SIZE(640, 480);

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
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 0.0f))
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
	ProgramNameSingle(0),
	ProgramNameMultiple(0)
{}

sample::~sample()
{}

bool sample::check() const
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Version = (MajorVersion * 10 + MinorVersion) >= (SAMPLE_MAJOR_VERSION * 10 + SAMPLE_MINOR_VERSION);
	return Version && glf::checkError("sample::check");
}

bool sample::begin(glm::ivec2 const & WindowSize)
{
	this->WindowSize = WindowSize;
	this->Viewport[TEXTURE_RGB8] = glm::ivec4(0, 0, this->WindowSize >> 1);
	this->Viewport[TEXTURE_R] = glm::ivec4(this->WindowSize.x >> 1, 0, this->WindowSize >> 1);
	this->Viewport[TEXTURE_G] = glm::ivec4(this->WindowSize.x >> 1, this->WindowSize.y >> 1, this->WindowSize >> 1);
	this->Viewport[TEXTURE_B] = glm::ivec4(0, this->WindowSize.y >> 1, this->WindowSize >> 1);

	bool Validated = true;
	if(Validated)
		Validated = this->initBlend();
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
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramNameMultiple);
	glDeleteProgram(ProgramNameSingle);
	glDeleteTextures(TEXTURE_MAX, Texture2DName);
	glDeleteFramebuffers(1, &FramebufferName);

	return glf::checkError("sample::end");
}

void sample::render()
{
	// Pass 1
	{
		// Compute the MVP (Model View Projection matrix)
		glm::mat4 Projection = glm::ortho(-1.0f, 1.0f,-1.0f, 1.0f, -1.0f, 1.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 View = ViewTranslate;
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glBindFramebuffer(GL_FRAMEBUFFER, this->FramebufferName);
		glViewport(0, 0, FRAMEBUFFER_SIZE.x >> 1, FRAMEBUFFER_SIZE.y >> 1);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(this->ProgramNameMultiple);
		glUniformMatrix4fv(this->UniformMVPMultiple, 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(this->UniformDiffuseMultiple, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->Texture2DName[TEXTURE_RGB8]);

		glBindVertexArray(this->VertexArrayName);
		glDrawArrays(GL_TRIANGLES, 0, VertexCount);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// Pass 2
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->ProgramNameSingle);

	{
		glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f);
		glm::mat4 View = glm::mat4(1.0f);
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glUniformMatrix4fv(this->UniformMVPSingle, 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(this->UniformDiffuseSingle, 0);
	}

	for(std::size_t i = 0; i < TEXTURE_MAX; ++i)
	{
		glViewport(Viewport[i].x, Viewport[i].y, Viewport[i].z, Viewport[i].w);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->Texture2DName[i]);

		glBindVertexArray(this->VertexArrayName);
		glDrawArrays(GL_TRIANGLES, 0, VertexCount);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

GLuint initShader(std::string const & Filename, GLenum Stage)
{
	bool Validated = true;

	GLuint ShaderName = 0;
	if(Validated)
	{
		std::string Source0 = glf::loadFile(Filename);
		char const * Source = Source0.c_str();
		ShaderName = glCreateShader(Stage);
		glShaderSource(ShaderName, 1, &Source, NULL);
		glCompileShader(ShaderName);
		Validated = glf::checkShader(ShaderName, Source);
	}
	
	glf::checkError("initShader");

	return ShaderName;
}

bool sample::initProgram()
{
	bool Validated = true;

	{
		if(Validated)
		{
			ProgramNameMultiple = glf::createProgram(VERTEX_SHADER_SOURCE1, FRAGMENT_SHADER_SOURCE1);
			glLinkProgram(ProgramNameMultiple);
			Validated = glf::checkProgram(ProgramNameMultiple);
		}

		if(Validated)
		{
			UniformMVPMultiple = glGetUniformLocation(ProgramNameMultiple, "MVP");
			UniformDiffuseMultiple = glGetUniformLocation(ProgramNameMultiple, "Diffuse");
		}
	}

	{
		if(Validated)
		{
			ProgramNameSingle = glf::createProgram(VERTEX_SHADER_SOURCE2, FRAGMENT_SHADER_SOURCE2);
			glLinkProgram(ProgramNameSingle);
			Validated = glf::checkProgram(ProgramNameSingle);
		}

		if(Validated)
		{
			UniformMVPSingle = glGetUniformLocation(ProgramNameSingle, "MVP");
			UniformDiffuseSingle = glGetUniformLocation(ProgramNameSingle, "Diffuse");
		}
	}

	return glf::checkError("sample::initProgram");
}

bool sample::initArrayBuffer()
{
	glGenBuffers(1, &BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("sample::initArrayBuffer");
}

bool sample::initTexture2D()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(TEXTURE_MAX, Texture2DName);

	gli::image Image = gli::import_as(TEXTURE_DIFFUSE);

	// Load image
	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[TEXTURE_RGB8]);
		// Set filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
	}

	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[TEXTURE_R]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ZERO);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ZERO);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ZERO);
	}
	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[TEXTURE_G]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_ZERO);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ZERO);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ZERO);
	}
	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[TEXTURE_B]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_ZERO);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ZERO);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ZERO);
	}

	// Set filter
	for(int i = TEXTURE_R; i <= TEXTURE_B; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			GL_RED,
			GLsizei(Image[0].dimensions().x), 
			GLsizei(Image[0].dimensions().y), 
			0,  
			GL_RGB, 
			GL_UNSIGNED_BYTE, 
			0);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return glf::checkError("initTexture2D");
}

bool sample::initFramebuffer()
{
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	for(std::size_t i = TEXTURE_R; i <= TEXTURE_B; ++i)
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GLenum(i - TEXTURE_R), GL_TEXTURE_2D, Texture2DName[i], 0);

	GLenum DrawBuffers[3];
	DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
	DrawBuffers[1] = GL_COLOR_ATTACHMENT1;
	DrawBuffers[2] = GL_COLOR_ATTACHMENT2;

	glDrawBuffers(3, DrawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
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

bool sample::initBlend()
{
	glEnablei(GL_BLEND, 0);
	glBlendEquationSeparatei(0, GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
	glBlendFuncSeparatei(0, GL_SRC_COLOR, GL_ONE, GL_ZERO, GL_ZERO);
	glColorMaski(0, GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

	glEnablei(GL_BLEND, 1);
	glBlendEquationSeparatei(1, GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparatei(1, GL_SRC_COLOR, GL_SRC_COLOR, GL_ZERO, GL_ZERO);
	glColorMaski(1, GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

	glEnablei(GL_BLEND, 2);
	glBlendEquationSeparatei(2, GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparatei(2, GL_SRC_COLOR, GL_SRC_COLOR, GL_ZERO, GL_ZERO);
	glColorMaski(2, GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

	glEnablei(GL_BLEND, 3);
	glBlendEquationSeparatei(3, GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparatei(3, GL_SRC_COLOR, GL_SRC_COLOR, GL_ZERO, GL_ZERO);
	glColorMaski(3, GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

	return glf::checkError("sample::initBlend");
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
		return 0;
	}

	fprintf(stderr, "OpenGL Error: this sample failed to run\n");

	delete Sample;
	Sample = 0;
	return 1;
}
