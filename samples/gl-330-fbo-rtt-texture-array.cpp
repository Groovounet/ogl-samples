//**********************************
// OpenGL Render to texture
// 20/10/2009 - 16/06/2010
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
	std::string const SAMPLE_NAME = "OpenGL Render to texture";
	std::string const VERTEX_SHADER_SOURCE1(glf::DATA_DIRECTORY + "gl-330/multiple-output.vert");
	std::string const FRAGMENT_SHADER_SOURCE1(glf::DATA_DIRECTORY + "gl-330/multiple-output.frag");
	std::string const VERTEX_SHADER_SOURCE2(glf::DATA_DIRECTORY + "gl-330/rtt-array.vert");
	std::string const FRAGMENT_SHADER_SOURCE2(glf::DATA_DIRECTORY + "gl-330/rtt-array.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken3-bgr8.dds");
	glm::ivec2 const FRAMEBUFFER_SIZE(320, 240);
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(3);
	int const SAMPLE_MINOR_VERSION(3);

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
	GLuint VertexArrayMultipleName = 0;
	GLuint VertexArrayImageName = 0;

	GLuint ProgramNameSingle = 0;
	GLint UniformMVPSingle = 0;
	GLint UniformDiffuseSingle = 0;
	GLint UniformLayer = 0;

	GLuint ProgramNameMultiple = 0;
	GLint UniformMVPMultiple = 0;
	GLint UniformDiffuseMultiple = 0;

	GLuint BufferName = 0;
	GLuint Texture2DName = 0;
	GLuint SamplerName = 0;

	glm::ivec4 Viewport[TEXTURE_MAX];
}//namespace

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool initProgram()
{
	bool Validated = true;

	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE1);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE1);

		ProgramNameMultiple = glCreateProgram();
		glAttachShader(ProgramNameMultiple, VertexShaderName);
		glAttachShader(ProgramNameMultiple, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramNameMultiple);
		Validated = glf::checkProgram(ProgramNameMultiple);
	}

	if(Validated)
	{
		UniformMVPMultiple = glGetUniformLocation(ProgramNameMultiple, "MVP");
	}

	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE2);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE2);

		ProgramNameSingle = glCreateProgram();
		glAttachShader(ProgramNameSingle, VertexShaderName);
		glAttachShader(ProgramNameSingle, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramNameSingle);
		Validated = glf::checkProgram(ProgramNameSingle);
	}

	if(Validated)
	{
		UniformMVPSingle = glGetUniformLocation(ProgramNameSingle, "MVP");
		UniformDiffuseSingle = glGetUniformLocation(ProgramNameSingle, "Diffuse");
		UniformLayer = glGetUniformLocation(ProgramNameSingle, "Layer");
	}

	return glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initTexture2D()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &Texture2DName);

	glBindTexture(GL_TEXTURE_2D_ARRAY, Texture2DName);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1000);

	glTexImage3D(
		GL_TEXTURE_2D_ARRAY, 
		0, 
		GL_RGB8, 
		GLsizei(FRAMEBUFFER_SIZE.x), 
		GLsizei(FRAMEBUFFER_SIZE.y), 
		GLsizei(3), //depth
		0,  
		GL_BGR, 
		GL_UNSIGNED_BYTE, 
		NULL);

	return glf::checkError("initTexture2D");
}

bool initFramebuffer()
{
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	GLenum DrawBuffers[3];
	DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
	DrawBuffers[1] = GL_COLOR_ATTACHMENT1;
	DrawBuffers[2] = GL_COLOR_ATTACHMENT2;
	glDrawBuffers(3, DrawBuffers);

	for(std::size_t i = TEXTURE_R; i <= TEXTURE_B; ++i)
		glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GLuint(i - TEXTURE_R), Texture2DName, 0, GLint(i));

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return glf::checkError("initFramebuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayMultipleName);
    glBindVertexArray(VertexArrayMultipleName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VertexArrayImageName);
    glBindVertexArray(VertexArrayImageName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initSampler()
{
	glGenSamplers(1, &SamplerName);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glSamplerParameterfv(SamplerName, GL_TEXTURE_BORDER_COLOR, &glm::vec4(0.0f)[0]);
	glSamplerParameterf(SamplerName, GL_TEXTURE_MIN_LOD, -1000.f);
	glSamplerParameterf(SamplerName, GL_TEXTURE_MAX_LOD, 1000.f);
	glSamplerParameterf(SamplerName, GL_TEXTURE_LOD_BIAS, 0.0f);
	glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glBindSampler(0, SamplerName);

	return glf::checkError("initSampler");
}

bool begin()
{
	Viewport[TEXTURE_R] = glm::ivec4(Window.Size.x >> 1, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Viewport[TEXTURE_G] = glm::ivec4(Window.Size.x >> 1, Window.Size.y >> 1, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Viewport[TEXTURE_B] = glm::ivec4(0, Window.Size.y >> 1, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);

	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_ARB_viewport_array");
	Validated = Validated && glf::checkExtension("GL_ARB_separate_shader_objects");

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
		Validated = initFramebuffer();
	if(Validated)
		Validated = initSampler();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramNameMultiple);
	glDeleteProgram(ProgramNameSingle);
	glDeleteTextures(1, &Texture2DName);
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteVertexArrays(1, &VertexArrayMultipleName);
	glDeleteVertexArrays(1, &VertexArrayImageName);

	return glf::checkError("end");
}

void display()
{
	// Pass 1
	{
		// Compute the MVP (Model View Projection matrix)
		glm::mat4 Projection = glm::ortho(-1.0f, 1.0f,-1.0f, 1.0f, -1.0f, 1.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 View = ViewTranslate;
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glProgramUniformMatrix4fv(ProgramNameMultiple, UniformMVPMultiple, 1, GL_FALSE, &MVP[0][0]);

		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewportIndexedf(0, 0, 0, float(FRAMEBUFFER_SIZE.x), float(FRAMEBUFFER_SIZE.y));
		glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		glUseProgram(ProgramNameMultiple);

		glBindVertexArray(VertexArrayMultipleName);
		glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 1);
	}

	// Pass 2
	{
		glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f);
		glm::mat4 View = glm::mat4(1.0f);
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glProgramUniformMatrix4fv(ProgramNameSingle, UniformMVPSingle, 1, GL_FALSE, &MVP[0][0]);
		glProgramUniform1i(ProgramNameSingle, UniformDiffuseSingle, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
		glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		glUseProgram(ProgramNameSingle);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, Texture2DName);

	glBindVertexArray(VertexArrayImageName);

	for(std::size_t i = 0; i < TEXTURE_MAX; ++i)
	{
		glViewportIndexedfv(0, &glm::vec4(Viewport[i])[0]);
		glProgramUniform1i(ProgramNameSingle, UniformLayer, GLint(i));

		glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 1);
	}

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT), 
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		SAMPLE_MAJOR_VERSION, 
		SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}
