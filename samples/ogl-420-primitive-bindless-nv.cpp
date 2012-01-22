//**********************************
// OpenGL Bindless 
// 09/03/2011
//**********************************
// Christophe Riccio
// ogl-samples@g-truc.net
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>
#include <gli/gtx/loader_dds9.hpp>
#include <gli/gtx/loader_dds10.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Bindless";
	std::string const SHADER_VERT_SOURCE(glf::DATA_DIRECTORY + "ogl-420/texture-2d.vert");
	std::string const SHADER_FRAG_SOURCE(glf::DATA_DIRECTORY + "ogl-420/texture-2d.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken256-rgb8.dds");
	std::string const TEXTURE_DIFFUSE_DXT1(glf::DATA_DIRECTORY + "kueken256-bc1-saved.dds");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

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
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		vertex(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		vertex(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		vertex(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f))
	};

	namespace program
	{
		enum type
		{
			VERTEX,
			FRAGMENT,
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

	GLuint VertexArrayName(0);
	GLuint PipelineName(0);
	GLuint ProgramName[program::MAX];

	GLuint BufferName[buffer::MAX] = {0, 0};
	GLuint Texture2DName(0);

	GLint UniformMVP(0);
	GLint UniformDiffuse(0);

	GLuint64EXT Address(0);

}//namespace

bool initProgram()
{
	bool Validated = true;

	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);
	glBindProgramPipeline(0);

	if(Validated)
	{
		GLuint VertShader = glf::createShader(GL_VERTEX_SHADER, SHADER_VERT_SOURCE);

		ProgramName[program::VERTEX] = glCreateProgram();
		glProgramParameteri(ProgramName[program::VERTEX], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[program::VERTEX], VertShader);
		glDeleteShader(VertShader);
		glLinkProgram(ProgramName[program::VERTEX]);
		Validated = Validated && glf::checkProgram(ProgramName[program::VERTEX]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, ProgramName[program::VERTEX]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	if(Validated)
	{
		GLuint FragShader = glf::createShader(GL_FRAGMENT_SHADER, SHADER_FRAG_SOURCE);

		ProgramName[program::FRAGMENT] = glCreateProgram();
		glProgramParameteri(ProgramName[program::FRAGMENT], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName[program::FRAGMENT], FragShader);
		glDeleteShader(FragShader);
		glLinkProgram(ProgramName[program::FRAGMENT]);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAGMENT]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAGMENT]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	return glf::checkError("initProgram");
}

bool initBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glGetBufferParameterui64vNV(GL_ARRAY_BUFFER, GL_BUFFER_GPU_ADDRESS_NV, &Address);
	glMakeBufferResidentNV(GL_ARRAY_BUFFER, GL_READ_ONLY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return glf::checkError("initBuffer");;
}

bool initTexture2D()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	gli::texture2D Texture = gli::load(TEXTURE_DIFFUSE);

	glGenTextures(1, &Texture2DName);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture2DName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(Texture.levels() - 1));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

	// Set image
	for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGBA8, 
			GLsizei(Texture[Level].dimensions().x), 
			GLsizei(Texture[Level].dimensions().y), 
			0,  
			GL_BGR, 
			GL_UNSIGNED_BYTE, 
			Texture[Level].data());
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return glf::checkError("initTexture2D");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glVertexAttribFormatNV(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex));
		glVertexAttribFormatNV(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex));

		glEnableClientState(GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
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
	Validated = Validated && glf::checkExtension("GL_NV_shader_buffer_load");
	Validated = Validated && glf::checkExtension("GL_NV_vertex_buffer_unified_memory");

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initTexture2D();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteProgram(ProgramName[program::VERTEX]);
	glDeleteProgram(ProgramName[program::FRAGMENT]);
	glDeleteTextures(1, &Texture2DName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgramPipelines(1, &PipelineName);

	return glf::checkError("end");
}

void display()
{
	{
		// Compute the MVP (Model View Projection matrix)
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
		glm::mat4* Pointer = (glm::mat4*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(MVP), GL_MAP_WRITE_BIT);
		*Pointer = MVP;
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}

	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size.x, Window.Size.y)[0]);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

	glBindProgramPipeline(PipelineName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture2DName);
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);
	glBindVertexArray(VertexArrayName);

	glBufferAddressRangeNV(GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV, glf::semantic::attr::POSITION, Address, VertexSize);
	glBufferAddressRangeNV(GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV, glf::semantic::attr::TEXCOORD, Address + sizeof(glm::vec2), VertexSize - sizeof(glm::vec2));

	glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, VertexCount, 1, 0);

	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	return glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT), 
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB, ::SAMPLE_MAJOR_VERSION, 
		::SAMPLE_MINOR_VERSION);
}
