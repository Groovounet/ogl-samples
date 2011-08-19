//**********************************
// OpenGL Tessellation Pipeline
// 14/05/2010 - 21/09/2010
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
	std::string const SAMPLE_NAME = "OpenGL Tessellation Pipeline";	
	std::string const SAMPLE_VERT_SHADER(glf::DATA_DIRECTORY + "420/dsa-tess.vert");
	std::string const SAMPLE_CONT_SHADER(glf::DATA_DIRECTORY + "420/dsa-tess.cont");
	std::string const SAMPLE_EVAL_SHADER(glf::DATA_DIRECTORY + "420/dsa-tess.eval");
	std::string const SAMPLE_GEOM_SHADER(glf::DATA_DIRECTORY + "420/dsa-tess.geom");
	std::string const SAMPLE_FRAG_SHADER(glf::DATA_DIRECTORY + "420/dsa-tess.frag");
	std::string const TEXTURE_DIFFUSE_BC1(glf::DATA_DIRECTORY + "kueken256-bc1.dds");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fc4f);
	glf::vertex_v2fc4f const VertexData[VertexCount] =
	{
		glf::vertex_v2fc4f(glm::vec2(-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2(-1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
	};

	namespace program
	{
		enum type
		{
			VERT,
			FRAG,
			MAX
		};
	}//namespace program

	namespace buffer
	{
		enum type
		{
			VERTEX,
			TRANSFORM,
			MAX
		};
	}//namespace buffer

	namespace framebuffer
	{
		enum type
		{
			READ,
			DRAW,
			MAX
		};
	}//namespace framebuffer

	namespace texture
	{
		enum type
		{
			DIFFUSE,
			RESOLVED,
			MULTISAMPLED,
			DEPTH,
			MAX
		};
	}//namespace buffer

	GLuint PipelineName(0);
	GLuint VertexArrayName(0);
	GLuint SamplerName(0);
	GLuint TextureName[texture::MAX] = {0, 0, 0};
	GLuint ProgramName[program::MAX] = {0, 0};
	GLuint BufferName[buffer::MAX] = {0, 0};
	GLuint FramebufferName[framebuffer::MAX] = {0, 0};
}//namespace

bool initProgram()
{
	bool Validated = true;
	
	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);
	glBindProgramPipeline(0);

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, SAMPLE_VERT_SHADER);
		GLuint ContShaderName = glf::createShader(GL_TESS_CONTROL_SHADER, SAMPLE_CONT_SHADER);
		GLuint EvalShaderName = glf::createShader(GL_TESS_EVALUATION_SHADER, SAMPLE_EVAL_SHADER);
		GLuint GeomShaderName = glf::createShader(GL_GEOMETRY_SHADER, SAMPLE_GEOM_SHADER);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, SAMPLE_FRAG_SHADER);

		ProgramName[program::VERT] = glCreateProgram();
		ProgramName[program::FRAG] = glCreateProgram();
		glProgramParameteri(ProgramName[program::VERT], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glProgramParameteri(ProgramName[program::FRAG], GL_PROGRAM_SEPARABLE, GL_TRUE);

		glAttachShader(ProgramName[program::VERT], VertShaderName);
		glAttachShader(ProgramName[program::VERT], ContShaderName);
		glAttachShader(ProgramName[program::VERT], EvalShaderName);
		glAttachShader(ProgramName[program::VERT], GeomShaderName);
		glLinkProgram(ProgramName[program::VERT]);

		glAttachShader(ProgramName[program::FRAG], FragShaderName);
		glLinkProgram(ProgramName[program::FRAG]);

		glDeleteShader(VertShaderName);
		glDeleteShader(ContShaderName);
		glDeleteShader(EvalShaderName);
		glDeleteShader(GeomShaderName);
		glDeleteShader(FragShaderName);

		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT | GL_TESS_CONTROL_SHADER_BIT | GL_TESS_EVALUATION_SHADER_BIT | GL_GEOMETRY_SHADER_BIT, ProgramName[program::VERT]);
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(1, &VertexArrayName);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName[buffer::VERTEX], 
		glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName[buffer::VERTEX], 
		glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), sizeof(glm::vec2));
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::COLOR);

	return Validated && glf::checkError("initVertexArray");
}

bool initSampler()
{
	bool Validated(true);

	glGenSamplers(1, &SamplerName);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(SamplerName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glSamplerParameterfv(SamplerName, GL_TEXTURE_BORDER_COLOR, &glm::vec4(0.0f)[0]);
	glSamplerParameterf(SamplerName, GL_TEXTURE_MIN_LOD, -1000.f);
	glSamplerParameterf(SamplerName, GL_TEXTURE_MAX_LOD, 1000.f);
	glSamplerParameterf(SamplerName, GL_TEXTURE_LOD_BIAS, 0.0f);
	glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	return Validated && glf::checkError("initSampler");
}

bool initTexture()
{
	bool Validated(true);

	gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE_BC1);
	Validated = Validated && !Texture.empty();

	glGenTextures(texture::MAX, TextureName);

	// Create diffuse texture
	{
		glTextureParameteriEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTextureParameteriEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
		glTextureParameteriEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
		glTextureParameteriEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
		glTextureParameteriEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
		glTextureParameteriEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
		glTextureStorage2DEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D, GLint(Texture.levels()), GL_COMPRESSED_RGB_S3TC_DXT1_EXT, 
			GLsizei(Texture[0].dimensions().x), GLsizei(Texture[0].dimensions().y));

		for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
		{
			glCompressedTextureSubImage2DEXT(
				TextureName[texture::DIFFUSE],
				GL_TEXTURE_2D,
				GLint(Level),
				0, 0,
				GLsizei(Texture[Level].dimensions().x), 
				GLsizei(Texture[Level].dimensions().y), 
				GL_COMPRESSED_RGB_S3TC_DXT1_EXT, 
				GLsizei(Texture[Level].capacity()), 
				Texture[Level].data());
		}

		if(Texture.levels() == 1)
			glGenerateTextureMipmapEXT(TextureName[texture::DIFFUSE], GL_TEXTURE_2D);
	}

	// Create multisampled texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, TextureName[texture::MULTISAMPLED]);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, GLsizei(Window.Size.x), GLsizei(Window.Size.y), GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	// Create resolved texture
	assert(glTextureStorage2DEXT);
	glTextureStorage2DEXT(TextureName[texture::RESOLVED], GL_TEXTURE_2D, 1, GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y));

	// Create depth texture
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::DEPTH]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, GLsizei(Window.Size.x), GLsizei(Window.Size.y));
	glBindTexture(GL_TEXTURE_2D, 0);

	return Validated && glf::checkError("initTexture");
}

bool initFramebuffer()
{
	bool Validated(true);

	//glGenRenderbuffers(1, &ColorRenderbufferName);
	//glNamedRenderbufferStorageMultisampleEXT(ColorRenderbufferName, 4, GL_RGBA, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);

	glGenFramebuffers(framebuffer::MAX, FramebufferName);

	glNamedFramebufferTextureEXT(FramebufferName[framebuffer::READ], GL_COLOR_ATTACHMENT0, TextureName[texture::MULTISAMPLED], 0);
	glNamedFramebufferTextureEXT(FramebufferName[framebuffer::READ], GL_DEPTH_ATTACHMENT, TextureName[texture::DEPTH], 0);
	Validated = Validated && glCheckNamedFramebufferStatusEXT(FramebufferName[framebuffer::READ], GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;

    glNamedFramebufferTextureEXT(FramebufferName[framebuffer::DRAW], GL_COLOR_ATTACHMENT0, TextureName[texture::RESOLVED], 0);
	Validated = Validated && glCheckNamedFramebufferStatusEXT(FramebufferName[framebuffer::DRAW], GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;

	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	return Validated && glf::checkError("initFramebuffer");
}

bool initBuffer()
{
	bool Validated(true);

	glGenBuffers(buffer::MAX, BufferName);
	glNamedBufferDataEXT(BufferName[buffer::VERTEX], VertexSize, VertexData, GL_STATIC_DRAW);
	glNamedBufferDataEXT(BufferName[buffer::TRANSFORM], sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);

	return Validated && glf::checkError("initBuffer");
}

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated && glf::checkError("initDebugOutput");
}

bool begin()
{
	bool Validated(true);
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_EXT_direct_state_access");

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
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
	bool Validated(true);

	glDeleteSamplers(1, &SamplerName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteProgramPipelines(1, &PipelineName);
	for(std::size_t i = 0; i < program::MAX; ++i)
		glDeleteProgram(ProgramName[i]);

	return Validated && glf::checkError("end");
}

void display()
{
	// Asynchrone update of the uniform buffer
	{
		//glm::mat4* Pointer = (glm::mat4*)glMapNamedBufferRangeEXT(
		//	BufferName[buffer::TRANSFORM], 0,	sizeof(glm::mat4),
		//	GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;
		glNamedBufferSubDataEXT(BufferName[buffer::TRANSFORM], 0, sizeof(glm::mat4), &MVP[0][0]);

		//*Pointer = MVP;

		// Make sure the uniform buffer is uploaded
		//glUnmapBuffer(BufferName[buffer::TRANSFORM]);
	}

	// Step 1: Clear the framebuffer
	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size)[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Step 2: Render the scene in a multisampled framebuffer
	glEnable(GL_MULTISAMPLE);
	{
		// Bind rendering objects
		glBindProgramPipeline(PipelineName);
		glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);
		glBindVertexArray(VertexArrayName);

		glPatchParameteri(GL_PATCH_VERTICES, VertexCount);
		glDrawArraysInstancedBaseInstance(GL_PATCHES, 0, VertexCount, 1, 0);
	}
	glDisable(GL_MULTISAMPLE);

	// Step 2: Resolved multisampling
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FramebufferName[framebuffer::READ]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FramebufferName[framebuffer::DRAW]);
	glBlitFramebuffer(
		0, 0, Window.Size.x, Window.Size.y, 
		0, 0, Window.Size.x, Window.Size.y, 
		GL_COLOR_BUFFER_BIT, GL_NEAREST);

	// Step 3: Generated mipmaps
	glGenerateTextureMipmapEXT(TextureName[texture::RESOLVED], GL_TEXTURE_2D);

	//// Step 4: Render the colorbuffer from the multisampled framebuffer
	//renderFB(ColorTextureName);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	return glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT), 
		::SAMPLE_MAJOR_VERSION, 
		::SAMPLE_MINOR_VERSION);
}
