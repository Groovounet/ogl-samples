//**********************************
// OpenGL Texture barrier
// 11/03/2011 - 11/03/2011
//**********************************
// Christophe Riccio
// christophe.riccio@g-truc.net
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Texture barrier";
	std::string const VERT_SHADER_SOURCE_BLUR(glf::DATA_DIRECTORY + "410/texture-barrier-nv.vert");
	std::string const FRAG_SHADER_SOURCE_BLUR(glf::DATA_DIRECTORY + "410/texture-barrier-nv.frag");
	std::string const VERT_SHADER_SOURCE_DRAW(glf::DATA_DIRECTORY + "410/texture-2d.vert");
	std::string const FRAG_SHADER_SOURCE_DRAW(glf::DATA_DIRECTORY + "410/texture-2d.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken640-rgb8.dds");
	glm::ivec2 FRAMEBUFFER_SIZE(0);
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
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
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 0.0f))
	};

	GLuint VertexArrayName = 0;
	GLuint BufferName = 0;
	GLuint Texture2DName = 0;
	GLuint SamplerName = 0;
	GLuint ColorbufferName = 0;
	GLuint FramebufferName = 0;

	enum program 
	{
		PROGRAM_BLUR,
		PROGRAM_DRAW,
		PROGRAM_MAX
	};

	GLint UniformMVP[PROGRAM_MAX];
	GLint UniformDiffuse[PROGRAM_MAX];
	GLuint ProgramName[PROGRAM_MAX];

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE_BLUR);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE_BLUR);

		ProgramName[PROGRAM_BLUR] = glCreateProgram();
		glAttachShader(ProgramName[PROGRAM_BLUR], VertexShaderName);
		glAttachShader(ProgramName[PROGRAM_BLUR], FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramName[PROGRAM_BLUR]);
		Validated = Validated && glf::checkProgram(ProgramName[PROGRAM_BLUR]);
	}

	if(Validated)
	{
		UniformMVP[PROGRAM_BLUR] = glGetUniformLocation(ProgramName[PROGRAM_BLUR], "MVP");
		UniformDiffuse[PROGRAM_BLUR] = glGetUniformLocation(ProgramName[PROGRAM_BLUR], "Diffuse");
	}

	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE_DRAW);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE_DRAW);

		ProgramName[PROGRAM_DRAW] = glCreateProgram();
		glAttachShader(ProgramName[PROGRAM_DRAW], VertexShaderName);
		glAttachShader(ProgramName[PROGRAM_DRAW], FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramName[PROGRAM_DRAW]);
		Validated = Validated && glf::checkProgram(ProgramName[PROGRAM_DRAW]);
	}

	if(Validated)
	{
		UniformMVP[PROGRAM_DRAW] = glGetUniformLocation(ProgramName[PROGRAM_DRAW], "MVP");
		UniformDiffuse[PROGRAM_DRAW] = glGetUniformLocation(ProgramName[PROGRAM_DRAW], "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");;
}

bool initSampler()
{
	glGenSamplers(1, &SamplerName);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return glf::checkError("initSampler");
}

bool initTexture2D()
{
	gli::texture2D Image = gli::load(TEXTURE_DIFFUSE);
	FRAMEBUFFER_SIZE = Image[0].dimensions();

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &Texture2DName);
	glBindTexture(GL_TEXTURE_2D, Texture2DName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGBA8, 
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0,  
			GL_BGR, 
			GL_UNSIGNED_BYTE, 
			Image[Level].data());
	}

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &ColorbufferName);
	glBindTexture(GL_TEXTURE_2D, ColorbufferName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGBA8, 
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0,  
			GL_BGR, 
			GL_UNSIGNED_BYTE, 
			Image[Level].data());
	}

	//glActiveTexture(GL_TEXTURE0);
	//glGenTextures(1, &ColorbufferName);
	//glBindTexture(GL_TEXTURE_2D, ColorbufferName);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Image[0].dimensions().x, Image[0].dimensions().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glGenerateMipmap(GL_TEXTURE_2D);

	return glf::checkError("initTexture2D");
}

bool initFramebuffer()
{
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ColorbufferName, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return glf::checkError("initFramebuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initTexture2D();
	if(Validated)
		Validated = initSampler();
	if(Validated)
		Validated = initFramebuffer();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteTextures(1, &ColorbufferName);
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName[PROGRAM_BLUR]);
	glDeleteProgram(ProgramName[PROGRAM_DRAW]);
	glDeleteTextures(1, &Texture2DName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteSamplers(1, &SamplerName);

	return glf::checkError("end");
}

void renderScene
(
	GLuint TextureName
)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glBindSampler(0, SamplerName);

	glBindVertexArray(VertexArrayName);
	glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 1);

	glf::checkError("renderScene");
}

void display()
{
	static int FrameIndex = 0;
	FrameIndex = (FrameIndex + 1) % 256;

	glm::mat4 MVP = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glProgramUniform1i(ProgramName[PROGRAM_BLUR], UniformDiffuse[PROGRAM_BLUR], 0);
	glProgramUniform1i(ProgramName[PROGRAM_DRAW], UniformDiffuse[PROGRAM_DRAW], 0);
	glProgramUniformMatrix4fv(ProgramName[PROGRAM_BLUR], UniformMVP[PROGRAM_BLUR], 1, GL_FALSE, &MVP[0][0]);
	glProgramUniformMatrix4fv(ProgramName[PROGRAM_DRAW], UniformMVP[PROGRAM_DRAW], 1, GL_FALSE, &MVP[0][0]);

	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));

	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glUseProgram(ProgramName[PROGRAM_BLUR]);
	renderScene(FrameIndex ? ColorbufferName : Texture2DName);

	//glTextureBarrierNV();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(ProgramName[PROGRAM_DRAW]);
	renderScene(ColorbufferName);

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
