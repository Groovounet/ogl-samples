//**********************************
// OpenGL Programmable trilinear filtering
// 27/05/2010 - 23/08/2011
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
	std::string const SAMPLE_NAME = "OpenGL Programmable trilinear filtering";
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "ogl-420/sampler-fetch.vert");
	std::string const FRAG_SHADER_LIBRARY(glf::DATA_DIRECTORY + "ogl-420/sampler-library.frag");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "ogl-420/sampler-fetch.frag");
	std::string const TEXTURE_DIFFUSE_DXT5(glf::DATA_DIRECTORY + "kueken256-dxt5.dds");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

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

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

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

	namespace program
	{
		enum type
		{
			VERT,
			FRAG,
			MAX
		};
	}//namespace program

	GLuint VertexArrayName(0);
	GLuint PipelineName(0);
	GLuint ProgramName[program::MAX] = {0, 0};
	GLuint BufferName[buffer::MAX] = {0, 0, 0};
	GLuint TextureName(0);
	GLuint SamplerName(0);
}//namespace

bool initProgram()
{
	bool Validated = true;

	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE);
		GLuint LibShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_LIBRARY);

		ProgramName[program::VERT] = glCreateProgram();
		glProgramParameteri(ProgramName[program::VERT], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[program::VERT], VertShaderName);
		glLinkProgram(ProgramName[program::VERT]);

		ProgramName[program::FRAG] = glCreateProgram();
		glProgramParameteri(ProgramName[program::FRAG], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[program::FRAG], FragShaderName);
		glAttachShader(ProgramName[program::FRAG], LibShaderName);
		glLinkProgram(ProgramName[program::FRAG]);

		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);
		glDeleteShader(LibShaderName);

		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, ProgramName[program::VERT]);
		Validated = Validated && glf::checkError("initProgram - stage");
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	return Validated && glf::checkError("initProgram");
}

bool initBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return glf::checkError("initArrayBuffer");;
}

bool initTexture2D()
{
	gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE_DXT5);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(Texture.levels() - 1));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

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

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return glf::checkError("initTexture2D");
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
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initBuffer();
	if(Validated)
		Validated = initTexture2D();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteTextures(1, &TextureName);
	glDeleteSamplers(1, &SamplerName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgram(ProgramName[program::VERT]);
	glDeleteProgram(ProgramName[program::FRAG]);
	glDeleteProgramPipelines(1, &PipelineName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

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

		*Pointer = Projection * View * Model;

		// Make sure the uniform buffer is uploaded
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}

	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glBindProgramPipeline(PipelineName);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);

	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1, 0, 0);

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
