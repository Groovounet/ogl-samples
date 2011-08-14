//**********************************
// OpenGL Samples Pack 
// ogl-samples.g-truc.net
//**********************************
// OpenGL Texture 2D Compressed
// 29/09/2010 - 19/08/2011
//**********************************
// Christophe Riccio
// ogl-samples@g-truc.net
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>
#include <gli/gtx/gl_texture2d.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Texture 2D Compressed";
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "420/texture-2d.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "420/texture-2d.frag");
	std::string const TEXTURE_DIFFUSE_BC1(glf::DATA_DIRECTORY + "kueken256-bc1.dds");
	std::string const TEXTURE_DIFFUSE_BC3(glf::DATA_DIRECTORY + "kueken256-bc3.dds");
	std::string const TEXTURE_DIFFUSE_BC4(glf::DATA_DIRECTORY + "kueken256-bc4.dds");
	std::string const TEXTURE_DIFFUSE_BC6(glf::DATA_DIRECTORY + "kueken128-bc6h.dds");
	std::string const TEXTURE_DIFFUSE_BC7(glf::DATA_DIRECTORY + "kueken256-bc7.dds");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken256-rgb8.dds");

	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fv2f);
	glf::vertex_v2fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v2fv2f(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace buffer
	{
		enum type
		{
			VERTEX,
			ELEMENT,
			TRANSFORM,
			MAX
		};
	}//namespace buffer

	namespace texture
	{
		enum type
		{
			BC3,
			BC4,
			BC6,
			BC7,
			MAX
		};
	}//namespace texture

	GLuint VertexArrayName(0);
	GLuint ProgramName(0);

	GLuint SamplerName(0);
	GLuint BufferName[buffer::MAX] = {0, 0, 0};
	GLuint Texture2DName[texture::MAX] = {0, 0, 0, 0};

	glm::ivec4 Viewport[texture::MAX];

}//namespace

bool initProgram()
{
	bool Validated(true);
	
	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertShaderName);
		glAttachShader(ProgramName, FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	return Validated;
}

bool initArrayBuffer()
{
	bool Validated(true);

	glGenBuffers(1, &BufferName[buffer::ELEMENT]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &BufferName[buffer::VERTEX]);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return Validated;
}

bool initTexture2D()
{
	bool Validated(true);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(texture::MAX, Texture2DName);

	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[texture::BC7]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);//GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE_BC7);
		for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				GLint(Level),
				GL_COMPRESSED_RGBA_BPTC_UNORM_ARB,
				GLsizei(Texture[Level].dimensions().x), 
				GLsizei(Texture[Level].dimensions().y), 
				0, 
				GLsizei(Texture[Level].capacity()), 
				Texture[Level].data());
		}
	}

	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[texture::BC3]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE_BC3);
		for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				GLint(Level),
				GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
				GLsizei(Texture[Level].dimensions().x), 
				GLsizei(Texture[Level].dimensions().y), 
				0, 
				GLsizei(Texture[Level].capacity()), 
				Texture[Level].data());
		}
	}

	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[texture::BC4]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);

		gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE_BC4);
		for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				GLint(Level),
				GL_COMPRESSED_RED_RGTC1, //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
				GLsizei(Texture[Level].dimensions().x), 
				GLsizei(Texture[Level].dimensions().y), 
				0, 
				GLsizei(Texture[Level].capacity()), 
				Texture[Level].data());
		}
	}

	{
		glBindTexture(GL_TEXTURE_2D, Texture2DName[texture::BC6]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		gli::texture2D Image = gli::load(TEXTURE_DIFFUSE);
		for(std::size_t Level = 0; Level < Image.levels(); ++Level)
		{
			glTexImage2D(
				GL_TEXTURE_2D, 
				GLint(Level), 
				GL_RGB, 
				GLsizei(Image[Level].dimensions().x), 
				GLsizei(Image[Level].dimensions().y), 
				0,  
				GL_BGR, 
				GL_UNSIGNED_BYTE, 
				Image[Level].data());
		}
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return Validated;
}

bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

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
	glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glSamplerParameterfv(SamplerName, GL_TEXTURE_BORDER_COLOR, &glm::vec4(0.0f)[0]);
	glSamplerParameterf(SamplerName, GL_TEXTURE_MIN_LOD, -1000.f);
	glSamplerParameterf(SamplerName, GL_TEXTURE_MAX_LOD, 1000.f);
	glSamplerParameterf(SamplerName, GL_TEXTURE_LOD_BIAS, 0.0f);
	glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	return Validated;
}

bool initUniformBuffer()
{
	bool Validated(true);

	GLint UniformBufferOffset(0);

	glGetIntegerv(
		GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
		&UniformBufferOffset);

	{
		GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4)), UniformBufferOffset);

		glGenBuffers(1, &BufferName[buffer::TRANSFORM]);
		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
		glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

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
	Viewport[texture::BC3] = glm::ivec4(0, 0, Window.Size >> 1);
	Viewport[texture::BC7] = glm::ivec4(Window.Size.x >> 1, 0, Window.Size >> 1);
	Viewport[texture::BC6] = glm::ivec4(Window.Size.x >> 1, Window.Size.y >> 1, Window.Size >> 1);
	Viewport[texture::BC4] = glm::ivec4(0, Window.Size.y >> 1, Window.Size >> 1);

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
		Validated = initUniformBuffer();

	return Validated;
}

bool end()
{
	bool Validated(true);

	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteProgram(ProgramName);
	glDeleteTextures(texture::MAX, Texture2DName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteSamplers(1, &SamplerName);

	return Validated;
}

void display()
{
	// Asynchrone update of the uniform buffer
	{
		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);

		glm::mat4* Pointer = (glm::mat4*)glMapBufferRange(
			GL_UNIFORM_BUFFER, 0,	sizeof(glm::mat4),
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		*Pointer = Projection * View * Model;
	}

	// Clear the color buffer
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	// Bind draw inputs
	glUseProgram(ProgramName);

	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);
	glBindSampler(0, SamplerName);
	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);

	// Make sure the uniform buffer is uploaded
	glUnmapBuffer(GL_UNIFORM_BUFFER);

	// Draw each texture in different viewports
	for(std::size_t Index = 0; Index < texture::MAX; ++Index)
	{
		glViewportIndexedf(0, Viewport[Index].x, Viewport[Index].y, Viewport[Index].z, Viewport[Index].w);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture2DName[Index]);

		glDrawElementsInstancedBaseVertexBaseInstance(
			GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, 0, 1, 0, 0);
	}

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
