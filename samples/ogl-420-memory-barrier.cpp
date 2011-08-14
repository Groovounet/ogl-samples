//**********************************
// OpenGL Memory Barrier
// 11/03/2011 - 13/08/2011
//**********************************
// Christophe Riccio
// ogl-samples@g-truc.net
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Memory barrier";
	std::string const SHADER_VERT_SOURCE_BLUR(glf::DATA_DIRECTORY + "410/texture-barrier-nv.vert");
	std::string const SHADER_FRAG_SOURCE_BLUR(glf::DATA_DIRECTORY + "410/texture-barrier-nv.frag");
	std::string const SHADER_VERT_SOURCE_DRAW(glf::DATA_DIRECTORY + "410/texture-2d.vert");
	std::string const SHADER_FRAG_SOURCE_DRAW(glf::DATA_DIRECTORY + "410/texture-2d.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken640-rgb8.dds");
	glm::ivec2 FRAMEBUFFER_SIZE(0);
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

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
	GLsizei const VertexCount(6);
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

	GLuint VertexArrayName(0);
	GLuint BufferName(0);
	GLuint Texture2DName(0);
	GLuint SamplerName(0);
	GLuint ColorbufferName(0);
	GLuint FramebufferName(0);

	enum program 
	{
		PROGRAM_VERT_BLUR,
		PROGRAM_FRAG_BLUR,
		PROGRAM_VERT_DRAW,
		PROGRAM_FRAG_DRAW,
		PROGRAM_MAX
	};
	
	enum pipeline 
	{
		PIPELINE_BLUR,
		PIPELINE_DRAW,
		PIPELINE_MAX
	};

	GLuint ProgramName[PROGRAM_MAX];
	GLuint PipelineName[PIPELINE_MAX];
	GLint UniformMVP[PIPELINE_MAX];
	GLint UniformDiffuse[PIPELINE_MAX];
}//namespace

bool initProgram()
{
	bool Validated(true);
	
	glGenProgramPipelines(PIPELINE_MAX, PipelineName);
	glBindProgramPipeline(PipelineName[PIPELINE_BLUR]);
	glBindProgramPipeline(PipelineName[PIPELINE_DRAW]);
	glBindProgramPipeline(0);

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, SHADER_VERT_SOURCE_BLUR);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, SHADER_FRAG_SOURCE_BLUR);

		ProgramName[PROGRAM_VERT_BLUR] = glCreateProgram();
		glProgramParameteri(ProgramName[PROGRAM_VERT_BLUR], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[PROGRAM_VERT_BLUR], VertShaderName);
		glDeleteShader(VertShaderName);
		glLinkProgram(ProgramName[PROGRAM_VERT_BLUR]);
		Validated = Validated && glf::checkProgram(ProgramName[PROGRAM_VERT_BLUR]);

		ProgramName[PROGRAM_FRAG_BLUR] = glCreateProgram();
		glProgramParameteri(ProgramName[PROGRAM_FRAG_BLUR], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[PROGRAM_FRAG_BLUR], FragShaderName);
		glDeleteShader(FragShaderName);
		glLinkProgram(ProgramName[PROGRAM_FRAG_BLUR]);
		Validated = Validated && glf::checkProgram(ProgramName[PROGRAM_FRAG_BLUR]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName[PIPELINE_BLUR], GL_VERTEX_SHADER_BIT, ProgramName[PROGRAM_VERT_BLUR]);
		glUseProgramStages(PipelineName[PIPELINE_BLUR], GL_FRAGMENT_SHADER_BIT, ProgramName[PROGRAM_FRAG_BLUR]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	if(Validated)
	{
		UniformMVP[PIPELINE_BLUR] = glGetUniformLocation(ProgramName[PROGRAM_VERT_BLUR], "MVP");
		UniformDiffuse[PIPELINE_BLUR] = glGetUniformLocation(ProgramName[PROGRAM_FRAG_BLUR], "Diffuse");
	}

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, SHADER_VERT_SOURCE_DRAW);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, SHADER_FRAG_SOURCE_DRAW);

		ProgramName[PROGRAM_VERT_DRAW] = glCreateProgram();
		glProgramParameteri(ProgramName[PROGRAM_VERT_DRAW], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[PROGRAM_VERT_DRAW], VertShaderName);
		glDeleteShader(VertShaderName);
		glLinkProgram(ProgramName[PROGRAM_VERT_DRAW]);
		Validated = Validated && glf::checkProgram(ProgramName[PROGRAM_VERT_DRAW]);

		ProgramName[PROGRAM_FRAG_DRAW] = glCreateProgram();
		glProgramParameteri(ProgramName[PROGRAM_FRAG_DRAW], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[PROGRAM_FRAG_DRAW], FragShaderName);
		glDeleteShader(FragShaderName);
		glLinkProgram(ProgramName[PROGRAM_FRAG_DRAW]);
		Validated = Validated && glf::checkProgram(ProgramName[PROGRAM_FRAG_DRAW]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName[PIPELINE_DRAW], GL_VERTEX_SHADER_BIT, ProgramName[PROGRAM_VERT_DRAW]);
		glUseProgramStages(PipelineName[PIPELINE_DRAW], GL_FRAGMENT_SHADER_BIT, ProgramName[PROGRAM_FRAG_DRAW]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	if(Validated)
	{
		UniformMVP[PIPELINE_DRAW] = glGetUniformLocation(ProgramName[PROGRAM_VERT_DRAW], "MVP");
		UniformDiffuse[PIPELINE_DRAW] = glGetUniformLocation(ProgramName[PROGRAM_FRAG_DRAW], "Diffuse");
	}

	return Validated;
}

bool initArrayBuffer()
{
	bool Validated(true);

	glGenBuffers(1, &BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return Validated;
}

bool initSampler()
{
	bool Validated(true);

	glGenSamplers(1, &SamplerName);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return Validated;
}

bool initTexture2D()
{
	bool Validated(true);

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

	return Validated;
}

bool initFramebuffer()
{
	bool Validated(true);

	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ColorbufferName, 0);

	Validated = Validated && (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Validated;
}

bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

	return Validated;
}

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool begin()
{
	bool Validated(true);
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
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

	return Validated;
}

bool end()
{
	bool Validated(true);

	glDeleteTextures(1, &ColorbufferName);
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName[PROGRAM_VERT_BLUR]);
	glDeleteProgram(ProgramName[PROGRAM_FRAG_BLUR]);
	glDeleteProgram(ProgramName[PROGRAM_VERT_DRAW]);
	glDeleteProgram(ProgramName[PROGRAM_FRAG_DRAW]);
	glDeleteTextures(1, &Texture2DName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteSamplers(1, &SamplerName);
	glDeleteProgramPipelines(PROGRAM_MAX, ProgramName);

	return Validated;
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
}

void display()
{
	static int FrameIndex = 0;
	FrameIndex = (FrameIndex + 1) % 256;

	glm::mat4 MVP = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glProgramUniform1i(ProgramName[PROGRAM_FRAG_BLUR], UniformDiffuse[PIPELINE_BLUR], 0);
	glProgramUniform1i(ProgramName[PROGRAM_FRAG_DRAW], UniformDiffuse[PIPELINE_DRAW], 0);
	glProgramUniformMatrix4fv(ProgramName[PROGRAM_VERT_BLUR], UniformMVP[PIPELINE_BLUR], 1, GL_FALSE, &MVP[0][0]);
	glProgramUniformMatrix4fv(ProgramName[PROGRAM_VERT_DRAW], UniformMVP[PIPELINE_DRAW], 1, GL_FALSE, &MVP[0][0]);

	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));

	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glBindProgramPipeline(PipelineName[PIPELINE_BLUR]);

	glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
	renderScene(FrameIndex ? ColorbufferName : Texture2DName);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindProgramPipeline(PipelineName[PIPELINE_DRAW]);
	
	glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
	renderScene(ColorbufferName);

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
