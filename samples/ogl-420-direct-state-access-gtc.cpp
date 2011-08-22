//**********************************
// OpenGL Framebuffer Multisample
// 20/02/2011 - 22/08/2011
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
	std::string const SAMPLE_NAME = "OpenGL Framebuffer Multisample";	
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken320-rgb8.tga");
	glm::ivec2 const FRAMEBUFFER_SIZE(160, 120);
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(6);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fv2f);
	glf::vertex_v2fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v2fv2f(glm::vec2(-4.0f,-3.0f), glm::vec2(0.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 4.0f,-3.0f), glm::vec2(1.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 4.0f, 3.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2( 4.0f, 3.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2(-4.0f, 3.0f), glm::vec2(0.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2(-4.0f,-3.0f), glm::vec2(0.0f, 1.0f))
	};

	namespace program
	{
		enum type
		{
			THROUGH,
			RESOLVE_BOX,
			RESOLVE_NEAR,
			MAX
		};
	}//namespace program

	namespace buffer
	{
		enum type
		{
			VERTEX,
			TRANSFORM,
			BLIT,
			MAX
		};
	}//namespace buffer

	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "420/instanced-image-2d.vert");
	std::string const FRAG_SHADER_SOURCE[program::MAX] = 
	{
		glf::DATA_DIRECTORY + "420/instanced-image-2d.frag",
		glf::DATA_DIRECTORY + "420/multisample-box.frag",
		glf::DATA_DIRECTORY + "420/multisample-near.frag",
	};

	GLuint PipelineName[program::MAX] = {0, 0, 0};
	GLuint ProgramName[program::MAX] = {0, 0, 0};

	GLuint VertexArrayName = 0;
	GLuint BufferName[buffer::MAX] = {0, 0, 0};
	GLuint Texture2DName = 0;
	GLuint SamplerName = 0;
	
	GLuint MultisampleTextureName = 0;
	GLuint DepthTextureName = 0;
	GLuint ColorTextureName = 0;
	
	GLuint FramebufferRenderName = 0;
	GLuint FramebufferResolveName = 0;

	GLint UniformMVP[program::MAX];

}//namespace

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

bool initProgram()
{
	bool Validated = true;
	
	glGenProgramPipelines(program::MAX, PipelineName);

	for(int i = 0; i < program::MAX; ++i)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE[i]);

		ProgramName[i] = glCreateProgram();
		glProgramParameteri(ProgramName[i], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[i], VertShaderName);
		glAttachShader(ProgramName[i], FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		glLinkProgram(ProgramName[i]);
		Validated = Validated && glf::checkProgram(ProgramName[i]);

		glUseProgramStages(PipelineName[i], GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT, ProgramName[i]);

		UniformMVP[i] = glGetUniformLocation(ProgramName[i], "MVP");
	}

	return Validated && glf::checkError("initProgram");
}

bool initBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);
	glNamedBufferDataEXT(BufferName[buffer::VERTEX], VertexSize, VertexData, GL_STATIC_DRAW);
	glNamedBufferDataEXT(BufferName[buffer::TRANSFORM], sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
	glNamedBufferDataEXT(BufferName[buffer::BLIT], sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);

	return glf::checkError("initBuffer");;
}

bool initTexture()
{
	gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE);

	glGenTextures(1, &Texture2DName);
	glTextureImage2DEXT(Texture2DName, GL_TEXTURE_2D, 0, GL_RGB8, GLsizei(Texture[0].dimensions().x), GLsizei(Texture[0].dimensions().y), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//glTextureStorage2DEXT(Texture2DName, GL_TEXTURE_2D, GLint(Texture.levels()), GL_RGB8, GLsizei(Texture[0].dimensions().x), GLsizei(Texture[0].dimensions().y)); // Crash on AMD

	for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
	{
		glTextureSubImage2DEXT(
			Texture2DName,
			GL_TEXTURE_2D, 
			GLint(Level), 
			0, 0, 
			GLsizei(Texture[Level].dimensions().x), 
			GLsizei(Texture[Level].dimensions().y), 
			GL_RGB, 
			GL_UNSIGNED_BYTE, 
			Texture[Level].data());
	}

	if(Texture.levels() == 1)
		glGenerateTextureMipmapEXT(Texture2DName, GL_TEXTURE_2D);

	return glf::checkError("initTexture");
}

bool initFramebuffer()
{
	bool Validated(true);

	glGenTextures(1, &MultisampleTextureName);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, MultisampleTextureName);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y, GL_TRUE);

	glGenTextures(1, &DepthTextureName);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, DepthTextureName);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT24, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y, GL_TRUE);

	glGenFramebuffers(1, &FramebufferRenderName);
	glNamedFramebufferTextureEXT(FramebufferRenderName, GL_DEPTH_ATTACHMENT, DepthTextureName, 0);
	glNamedFramebufferTextureEXT(FramebufferRenderName, GL_COLOR_ATTACHMENT0, MultisampleTextureName, 0);
	Validated = Validated && (glCheckNamedFramebufferStatusEXT(FramebufferRenderName, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glGenTextures(1, &ColorTextureName);
	glBindTexture(GL_TEXTURE_2D, ColorTextureName);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenFramebuffers(1, &FramebufferResolveName);
	glNamedFramebufferTextureEXT(FramebufferResolveName, GL_COLOR_ATTACHMENT0, ColorTextureName, 0);
	Validated = Validated && (glCheckNamedFramebufferStatusEXT(FramebufferResolveName, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	return glf::checkError("initFramebuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName[buffer::VERTEX], 
		glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName[buffer::VERTEX], 
		glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), sizeof(glm::vec2));
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::TEXCOORD);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	//Validated = Validated && glf::checkExtension("GL_GTC_direct_state_access");

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initSampler();
	if(Validated)
		Validated = initTexture();
	if(Validated)
		Validated = initFramebuffer();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteProgramPipelines(program::MAX, PipelineName);
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteSamplers(1, &SamplerName);
	glDeleteTextures(1, &Texture2DName);
	glDeleteTextures(1, &ColorTextureName);
	glDeleteTextures(1, &MultisampleTextureName);
	glDeleteFramebuffers(1, &FramebufferRenderName);
	glDeleteFramebuffers(1, &FramebufferResolveName);
	glDeleteVertexArrays(1, &VertexArrayName);
	for(int i = 0; i < program::MAX; ++i)
		glDeleteProgram(ProgramName[i]);

	return glf::checkError("end");
}

void renderFBO(GLuint Framebuffer)
{
	glm::mat4 Perspective = glm::perspective(45.0f, float(FRAMEBUFFER_SIZE.x) / FRAMEBUFFER_SIZE.y, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y * 2.0 - 4.0));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Perspective * View * Model;
	glNamedBufferSubDataEXT(BufferName[buffer::TRANSFORM], 0, sizeof(glm::mat4), &MVP[0][0]);

	//glProgramUniformMatrix4fv(ProgramName[program::THROUGH], UniformMVP[program::THROUGH], 1, GL_FALSE, &MVP[0][0]);

	glEnable(GL_DEPTH_TEST);
	glViewportIndexedf(0, 0, 0, float(FRAMEBUFFER_SIZE.x), float(FRAMEBUFFER_SIZE.y));

	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);
	float Depth(1.0f);
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glBindProgramPipeline(PipelineName[program::THROUGH]);
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);
	glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, Texture2DName);
	glBindSampler(0, SamplerName);
	glBindVertexArray(VertexArrayName);

	glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, VertexCount, 5, 0);

	glDisable(GL_DEPTH_TEST);

	glf::checkError("renderFBO");
}

void resolveMultisampling()
{
	glm::mat4 Perspective = glm::perspective(45.0f, float(Window.Size.x) / Window.Size.y, 0.1f, 100.0f);
	glm::mat4 ViewFlip = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,-1.0f, 1.0f));
	glm::mat4 ViewTranslate = glm::translate(ViewFlip, glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y * 2.0));
	glm::mat4 View = glm::rotate(ViewTranslate,-15.f, glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Perspective * View * Model;
	glNamedBufferSubDataEXT(BufferName[buffer::BLIT], 0, sizeof(glm::mat4), &MVP[0][0]);

	//glProgramUniformMatrix4fv(ProgramName[program::RESOLVE_BOX], UniformMVP[program::RESOLVE_BOX], 1, GL_FALSE, &MVP[0][0]);
	//glProgramUniformMatrix4fv(ProgramName[program::RESOLVE_NEAR], UniformMVP[program::RESOLVE_NEAR], 1, GL_FALSE, &MVP[0][0]);

	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
	glEnable(GL_SCISSOR_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::BLIT]);
	glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D_MULTISAMPLE, MultisampleTextureName);
	glBindSampler(0, SamplerName);
	glBindVertexArray(VertexArrayName);

	// Box
	{
		glScissorIndexed(0, 1, 1, Window.Size.x  / 2 - 2, Window.Size.y - 2);
		glBindProgramPipeline(PipelineName[program::RESOLVE_BOX]);
		glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, VertexCount, 5, 0);
	}

	// Near
	{
		glScissorIndexed(0, Window.Size.x / 2 + 1, 1, Window.Size.x / 2 - 2, Window.Size.y - 2);
		glBindProgramPipeline(PipelineName[program::RESOLVE_NEAR]);
		glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, VertexCount, 5, 0);
	}

	glDisable(GL_SCISSOR_TEST);

	glf::checkError("renderFB");
}

void display()
{
	// Clear the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	// Pass 1
	// Render the scene in a multisampled framebuffer
	glEnable(GL_MULTISAMPLE);
	renderFBO(FramebufferRenderName);
	glDisable(GL_MULTISAMPLE);

	// Pass 2
	// Resolved and render the colorbuffer from the multisampled framebuffer
	resolveMultisampling();

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
