//**********************************
// OpenGL Multiple render to texture
// 20/10/2009 - 16/06/2010
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
	std::string const SAMPLE_NAME = "OpenGL Multiple render to texture";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/image-2d.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/image-2d.frag");
	glm::ivec2 const FRAMEBUFFER_SIZE(320, 240);
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 0;

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
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 0.0f))
	};

	enum texture_type
	{
		TEXTURE_R,
		TEXTURE_G,
		TEXTURE_B,
		TEXTURE_MAX
	};

	GLuint FramebufferName = 0;
	GLuint VertexArrayName = 0;

	GLuint ProgramNameSingle = 0;
	GLuint UniformMVPSingle = 0;
	GLuint UniformDiffuseSingle = 0;

	GLuint ProgramNameMultiple = 0;
	GLuint UniformMVPMultiple = 0;
	GLuint UniformDiffuseMultiple = 0;

	GLuint BufferName = 0;
	GLuint Texture2DName[TEXTURE_MAX];

	glm::ivec4 Viewport[TEXTURE_MAX];

}//namespace

bool initProgram()
{
	bool Validated = true;

	if(Validated)
	{
		ProgramNameSingle = glCreateProgram();

		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		glAttachShader(ProgramNameSingle, VertexShaderName);
		glDeleteShader(VertexShaderName);

		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);
		glAttachShader(ProgramNameSingle, FragmentShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramNameSingle);
		Validated = glf::checkProgram(ProgramNameSingle);
	}

	if(Validated)
	{
		UniformMVPSingle = glGetUniformLocation(ProgramNameSingle, "MVP");
		UniformDiffuseSingle = glGetUniformLocation(ProgramNameSingle, "Diffuse");
	}

	return glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);
    glNamedBufferDataEXT(BufferName, VertexSize, VertexData, GL_STATIC_DRAW);

	return glf::checkError("initArrayBuffer");
}

bool initTexture2D()
{
	glGenTextures(TEXTURE_MAX, Texture2DName);

	for(int i = TEXTURE_R; i <= TEXTURE_B; ++i)
	{
		glTextureParameteriEXT(Texture2DName[i], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
		glTextureParameteriEXT(Texture2DName[i], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
		glTextureParameteriEXT(Texture2DName[i], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
		glTextureParameteriEXT(Texture2DName[i], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
		glTextureParameteriEXT(Texture2DName[i], GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTextureParameteriEXT(Texture2DName[i], GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);

		glTextureImage2DEXT(
			Texture2DName[i], 
			GL_TEXTURE_2D, 
			0, 
			GL_RGB,
			GLsizei(FRAMEBUFFER_SIZE.x), 
			GLsizei(FRAMEBUFFER_SIZE.y), 
			0,  
			GL_RGB, 
			GL_UNSIGNED_BYTE, 
			0);
	}

	return glf::checkError("initTexture2D");
}

bool initFramebuffer()
{
	GLenum DrawBuffers[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glGenFramebuffers(1, &FramebufferName);
	glFramebufferDrawBuffersEXT(FramebufferName, 3, DrawBuffers);
	for(std::size_t i = TEXTURE_R; i <= TEXTURE_B; ++i)
		glNamedFramebufferTextureEXT(FramebufferName, GL_COLOR_ATTACHMENT0 + GLenum(i - TEXTURE_R), Texture2DName[i], 0);

	if(glCheckNamedFramebufferStatusEXT(FramebufferName, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	return glf::checkError("initFramebuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName, glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName, glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), sizeof(glm::vec2));

	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::TEXCOORD);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	Viewport[TEXTURE_R] = glm::ivec4(Window.Size.x >> 1, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Viewport[TEXTURE_G] = glm::ivec4(Window.Size.x >> 1, Window.Size.y >> 1, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Viewport[TEXTURE_B] = glm::ivec4(0, Window.Size.y >> 1, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);

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
	if(Validated)
		Validated = initTexture2D();
	if(Validated)
		Validated = initFramebuffer();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramNameMultiple);
	glDeleteProgram(ProgramNameSingle);
	glDeleteTextures(TEXTURE_MAX, Texture2DName);
	glDeleteFramebuffers(1, &FramebufferName);

	return glf::checkError("end");
}

void display()
{
	// Pass 1
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	glViewport(0, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)[0]);
	glClearBufferfv(GL_COLOR, 1, &glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)[0]);
	glClearBufferfv(GL_COLOR, 2, &glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)[0]);
	glClearBufferfv(GL_COLOR, 3, &glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)[0]);

	// Pass 2
	glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f);
	glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glProgramUniformMatrix4fvEXT(ProgramNameSingle, UniformMVPSingle, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform1iEXT(ProgramNameSingle, UniformDiffuseSingle, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glUseProgram(ProgramNameSingle);

	for(std::size_t i = 0; i < TEXTURE_MAX; ++i)
	{
		glViewport(Viewport[i].x, Viewport[i].y, Viewport[i].z, Viewport[i].w);

		glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, Texture2DName[i]);
		glBindVertexArray(VertexArrayName);

		glDrawArrays(GL_TRIANGLES, 0, VertexCount);
	}

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
