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
	std::string const SAMPLE_VERT_SHADER_BLIT(glf::DATA_DIRECTORY + "420/dsa-blit.vert");
	std::string const SAMPLE_FRAG_SHADER_BLIT(glf::DATA_DIRECTORY + "420/dsa-blit.frag");
	std::string const TEXTURE_DIFFUSE_BC1(glf::DATA_DIRECTORY + "kueken256-bc1.dds");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

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

	GLsizei const VertexBlitCount(3);
	GLsizeiptr const VertexBlitSize = VertexBlitCount * sizeof(glm::vec2);
	glm::vec2 const VertexBlitData[VertexCount] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(2.0f, 0.0f),
		glm::vec2(0.0f, 2.0f)
	};

	namespace program
	{
		enum type
		{
			VERT,
			FRAG,
			BLIT,
			MAX
		};
	}//namespace program

	namespace buffer
	{
		enum type
		{
			VERTEX,
			BLIT,
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

	namespace pipeline
	{
		enum type
		{
			MULTISAMPLE,
			RESOLVE,
			MAX
		};
	}//namespace pipeline

	GLuint PipelineName[pipeline::MAX] = {0, 0};
	GLuint VertexArrayName[pipeline::MAX] = {0, 0};
	GLuint SamplerName(0);
	GLuint TextureName[texture::MAX] = {0, 0, 0};
	GLuint ProgramName[program::MAX] = {0, 0};
	GLuint BufferName[buffer::MAX] = {0, 0};
	GLuint FramebufferName[framebuffer::MAX] = {0, 0};
}//namespace

bool initProgram()
{
	bool Validated = true;
	
	glGenProgramPipelines(pipeline::MAX, PipelineName);

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
		glUseProgramStages(PipelineName[pipeline::MULTISAMPLE], GL_VERTEX_SHADER_BIT | GL_TESS_CONTROL_SHADER_BIT | GL_TESS_EVALUATION_SHADER_BIT | GL_GEOMETRY_SHADER_BIT, ProgramName[program::VERT]);
		glUseProgramStages(PipelineName[pipeline::MULTISAMPLE], GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, SAMPLE_VERT_SHADER);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, SAMPLE_FRAG_SHADER);

		ProgramName[program::BLIT] = glCreateProgram();
		glProgramParameteri(ProgramName[program::BLIT], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[program::BLIT], VertShaderName);
		glAttachShader(ProgramName[program::BLIT], FragShaderName);
		glLinkProgram(ProgramName[program::BLIT]);

		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		Validated = Validated && glf::checkProgram(ProgramName[program::BLIT]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName[pipeline::MULTISAMPLE], GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT, ProgramName[program::BLIT]);
	}

	return Validated && glf::checkError("initProgram");
}
/*
bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(pipeline::MAX, VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName[pipeline::MULTISAMPLE], BufferName[buffer::VERTEX], 
		glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName[pipeline::MULTISAMPLE], BufferName[buffer::VERTEX], 
		glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), sizeof(glm::vec2));
	glEnableVertexArrayAttribEXT(VertexArrayName[pipeline::MULTISAMPLE], glf::semantic::attr::POSITION);
	glEnableVertexArrayAttribEXT(VertexArrayName[pipeline::MULTISAMPLE], glf::semantic::attr::COLOR);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName[pipeline::RESOLVE], BufferName[buffer::VERTEX], 
		glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
	glEnableVertexArrayAttribEXT(VertexArrayName[pipeline::RESOLVE], glf::semantic::attr::POSITION);

	return Validated && glf::checkError("initVertexArray");
}
*/
bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(pipeline::MAX, VertexArrayName);

    glBindVertexArray(VertexArrayName[pipeline::MULTISAMPLE]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);
	glBindVertexArray(0);

    glBindVertexArray(VertexArrayName[pipeline::RESOLVE]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), GLF_BUFFER_OFFSET(0));

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return Validated;
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

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, TextureName[texture::MULTISAMPLED]);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y), GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, TextureName[texture::DEPTH]);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT24, GLsizei(Window.Size.x), GLsizei(Window.Size.y), GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	//glTexImage2D(GL_TEXTURE_2D_MULTISAMPLE, GLint(0), GL_DEPTH_COMPONENT24, GLsizei(Window.Size.x), GLsizei(Window.Size.y),	0,  GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	// Create resolved texture
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::RESOLVED]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y));
	glBindTexture(GL_TEXTURE_2D, 0);
	//glTextureStorage2DEXT(TextureName[texture::RESOLVED], GL_TEXTURE_2D, 1, GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y));
/*
	// Create multisampled texture
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::MULTISAMPLED]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Create depth texture
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::DEPTH]);
	glTexImage2D(GL_TEXTURE_2D, GLint(0), GL_DEPTH_COMPONENT24, GLsizei(Window.Size.x), GLsizei(Window.Size.y),	0,  GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glTextureStorage2DEXT(TextureName[texture::DEPTH], GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, GLsizei(Window.Size.x), GLsizei(Window.Size.y));
*/
	return Validated && glf::checkError("initTexture");
}

bool initFramebuffer()
{
	bool Validated(true);

	//glGenRenderbuffers(1, &ColorRenderbufferName);
	//glNamedRenderbufferStorageMultisampleEXT(ColorRenderbufferName, 4, GL_RGBA, FRAMEBUFFER_SIZE.x, FRAMEBUFFER_SIZE.y);
	Validated = Validated && glf::checkError("initFramebuffer0");

	glGenFramebuffers(framebuffer::MAX, FramebufferName);

	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName[framebuffer::READ]);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, TextureName[texture::DEPTH], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, TextureName[texture::MULTISAMPLED], 0);
	Validated = Validated && (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	//glNamedFramebufferTextureEXT(FramebufferName[framebuffer::READ], GL_DEPTH_ATTACHMENT, TextureName[texture::DEPTH], 0);
	//glNamedFramebufferTextureEXT(FramebufferName[framebuffer::READ], GL_COLOR_ATTACHMENT0, TextureName[texture::MULTISAMPLED], 0);
	//Validated = Validated && (glCheckNamedFramebufferStatusEXT(FramebufferName[framebuffer::READ], GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glNamedFramebufferTextureEXT(FramebufferName[framebuffer::DRAW], GL_COLOR_ATTACHMENT0, TextureName[texture::RESOLVED], 0);
	Validated = Validated && (glCheckNamedFramebufferStatusEXT(FramebufferName[framebuffer::DRAW], GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	
	return Validated && glf::checkError("initFramebuffer");
}

bool initBuffer()
{
	bool Validated(true);

	glGenBuffers(buffer::MAX, BufferName);
	glNamedBufferDataEXT(BufferName[buffer::VERTEX], VertexSize, VertexData, GL_STATIC_DRAW);
	glNamedBufferDataEXT(BufferName[buffer::TRANSFORM], sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);

	// To be deleted
	glNamedBufferDataEXT(BufferName[buffer::BLIT], VertexBlitSize, VertexBlitData, GL_STATIC_DRAW);

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
	glDeleteVertexArrays(pipeline::MAX, VertexArrayName);
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteProgramPipelines(pipeline::MAX, PipelineName);
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

	GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0};

	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size)[0]);

	// Step 1: Render the scene in a multisampled framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);//FramebufferName[framebuffer::READ]);
	//glDrawBuffers(1, DrawBuffers);

	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_MULTISAMPLE);
	{
		// Bind rendering objects
		glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);
		glBindProgramPipeline(PipelineName[pipeline::MULTISAMPLE]);
		glBindVertexArray(VertexArrayName[pipeline::MULTISAMPLE]);

		glPatchParameteri(GL_PATCH_VERTICES, VertexCount);
		glDrawArraysInstancedBaseInstance(GL_PATCHES, 0, VertexCount, 1, 0);
	}
	glDisable(GL_MULTISAMPLE);

	// Step 2: Render the colorbuffer from the multisampled framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDrawBuffers(1, DrawBuffers);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	{
		// No actual need to update it
		glm::mat4 MVP = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f,-1.0f, 1.0f);
		glNamedBufferSubDataEXT(BufferName[buffer::BLIT], 0, sizeof(glm::mat4), &MVP[0][0]);

		glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::BLIT]);
		glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, TextureName[texture::DIFFUSE]);
		glBindProgramPipeline(PipelineName[pipeline::RESOLVE]);
		glBindVertexArray(VertexArrayName[pipeline::RESOLVE]);

		glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, VertexCount, 1, 0);
	}

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
