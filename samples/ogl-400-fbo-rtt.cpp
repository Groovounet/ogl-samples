//**********************************
// OpenGL Render to texture
// 20/10/2009 - 28/08/2010
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
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/image-2d.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/image-2d.frag");
	glm::ivec2 const FRAMEBUFFER_SIZE(320, 240);
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(0);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 4;
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fv2f);
	glf::vertex_v2fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v2fv2f(glm::vec2(-4.0f,-3.0f), glm::vec2(0.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2( 4.0f,-3.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2( 4.0f, 3.0f), glm::vec2(1.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2(-4.0f, 3.0f), glm::vec2(0.0f, 1.0f))
	};

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	enum buffer_type
	{
		BUFFER_VERTEX,
		BUFFER_ELEMENT,
		BUFFER_MAX
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

	GLuint ProgramName = 0;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;
	GLuint SamplerName = 0;

	GLuint BufferName[BUFFER_MAX];
	GLuint Texture2DName[TEXTURE_MAX];

	glm::ivec4 Viewport[TEXTURE_MAX];

}//namespace

bool initProgram()
{
	bool Validated = true;

	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertexShaderName);
		glAttachShader(ProgramName, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	return glf::checkError("initProgram");
}

bool initVertexBuffer()
{
	glGenBuffers(BUFFER_MAX, BufferName);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[BUFFER_ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initTexture2D()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(TEXTURE_MAX, Texture2DName);

	for(int i = TEXTURE_R; i <= TEXTURE_B; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(
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
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Texture2DName[0], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, Texture2DName[1], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, Texture2DName[2], 0);
	GLenum DrawBuffers[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, DrawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return glf::checkError("initFramebuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
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

	return glf::checkError("initSampler");
}

bool begin()
{
	Viewport[TEXTURE_R] = glm::ivec4(Window.Size.x >> 1, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Viewport[TEXTURE_G] = glm::ivec4(Window.Size.x >> 1, Window.Size.y >> 1, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Viewport[TEXTURE_B] = glm::ivec4(0, Window.Size.y >> 1, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);

	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initVertexBuffer();
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
	glDeleteBuffers(BUFFER_MAX, BufferName);
	glDeleteTextures(TEXTURE_MAX, Texture2DName);
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteProgram(ProgramName);
	glDeleteSamplers(1, &SamplerName);

	return glf::checkError("end");
}

void display()
{
	GLint const Border = 16;

	// Pass 1
	glBindSampler(0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0, 0, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);

	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)[0]);
	glClearBufferfv(GL_COLOR, 1, &glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)[0]);
	glClearBufferfv(GL_COLOR, 2, &glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)[0]);

	// Pass 2
	glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f);
	glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glUseProgram(ProgramName);
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(UniformDiffuse, 0);

	glBindSampler(0, SamplerName);

	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[BUFFER_ELEMENT]);

	for(std::size_t i = 0; i < TEXTURE_MAX; ++i)
	{
		glViewport(Viewport[i].x, Viewport[i].y, Viewport[i].z, Viewport[i].w);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture2DName[i]);

		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1, 0);
	}

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	if(glf::run(
		argc, argv,
		glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT), 
		SAMPLE_MAJOR_VERSION, 
		SAMPLE_MINOR_VERSION))
		return 0;
	return 1;
}
