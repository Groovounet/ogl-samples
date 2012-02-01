//**********************************
// OpenGL Samples Pack 
// ogl-samples.g-truc.net
//**********************************
// OpenGL Image Store
// 21/11/2011 - 21/11/2011
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
	std::string const SAMPLE_NAME("OpenGL Image Store");
	std::string const VERT_SHADER_SOURCE_SAVE(glf::DATA_DIRECTORY + "ogl-420/image-store-write.vert");
	std::string const FRAG_SHADER_SOURCE_SAVE(glf::DATA_DIRECTORY + "ogl-420/image-store-write.frag");
	std::string const VERT_SHADER_SOURCE_READ(glf::DATA_DIRECTORY + "ogl-420/image-store-read.vert");
	std::string const FRAG_SHADER_SOURCE_READ(glf::DATA_DIRECTORY + "ogl-420/image-store-read.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	namespace program
	{
		enum type
		{
			VERT,
			FRAG,
			MAX
		};
	}//namespace program

	namespace pipeline
	{
		enum type
		{
			READ,
			SAVE,
			MAX
		};
	}//namespace pipeline

	glm::uvec2 ImageSize(0);

	GLuint VertexArrayName(0);
	GLuint PipelineName[pipeline::MAX] = {0, 0};
	GLuint ProgramName[program::MAX] = {0, 0};
	GLuint TextureName(0);
}//namespace

bool initProgram()
{
	bool Validated(true);

	glGenProgramPipelines(pipeline::MAX, PipelineName);

	glBindProgramPipeline(PipelineName[pipeline::READ]);
	if(Validated)
	{
		std::string VertexSourceContent = glf::loadFile(VERT_SHADER_SOURCE_READ);
		char const * VertexSourcePointer = VertexSourceContent.c_str();
		ProgramName[program::VERT] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &VertexSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
	}

	if(Validated)
	{
		std::string FragmentSourceContent = glf::loadFile(FRAG_SHADER_SOURCE_READ);
		char const * FragmentSourcePointer = FragmentSourceContent.c_str();
		ProgramName[program::FRAG] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &FragmentSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName[pipeline::READ], GL_VERTEX_SHADER_BIT, ProgramName[program::VERT]);
		glUseProgramStages(PipelineName[pipeline::READ], GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	glBindProgramPipeline(PipelineName[pipeline::SAVE]);
	if(Validated)
	{
		std::string VertexSourceContent = glf::loadFile(VERT_SHADER_SOURCE_SAVE);
		char const * VertexSourcePointer = VertexSourceContent.c_str();
		ProgramName[program::VERT] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &VertexSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
	}

	if(Validated)
	{
		std::string FragmentSourceContent = glf::loadFile(FRAG_SHADER_SOURCE_SAVE);
		char const * FragmentSourcePointer = FragmentSourceContent.c_str();
		ProgramName[program::FRAG] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &FragmentSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName[pipeline::SAVE], GL_VERTEX_SHADER_BIT, ProgramName[program::VERT]);
		glUseProgramStages(PipelineName[pipeline::SAVE], GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	return Validated;
}

bool initTexture()
{
	bool Validated(true);

	glGenTextures(1, &TextureName);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexStorage2D(GL_TEXTURE_2D, GLint(1), GL_RGBA8, GLsizei(Window.Size.x), GLsizei(Window.Size.y));

	return Validated;
}

bool initVertexArray()
{
	bool Validated(true);

	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
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
		Validated = initTexture();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initVertexArray();

	return Validated;
}

bool end()
{
	bool Validated(true);

	glDeleteTextures(1, &TextureName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgram(ProgramName[program::VERT]);
	glDeleteProgram(ProgramName[program::FRAG]);
	glDeleteProgramPipelines(pipeline::MAX, PipelineName);

	return Validated;
}

void display()
{
	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
	glDrawBuffer(GL_BACK);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.5f, 1.0f, 1.0f)[0]);

	// Renderer to image
	{
		glDrawBuffer(GL_NONE);

		glBindProgramPipeline(PipelineName[pipeline::SAVE]);
		glBindImageTexture(glf::semantic::image::DIFFUSE, TextureName, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
		glBindVertexArray(VertexArrayName);
		glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 3, 1, 0);
	}

	// Read from image
	{
		GLint Border(8);
		glEnable(GL_SCISSOR_TEST);
		glScissorIndexed(0, Border, Border, Window.Size.x - 2 * Border, Window.Size.y - 2 * Border);

		glDrawBuffer(GL_BACK);

		glBindProgramPipeline(PipelineName[pipeline::READ]);
		glBindImageTexture(glf::semantic::image::DIFFUSE, TextureName, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		glBindVertexArray(VertexArrayName);
		glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 3, 1, 0);

		glDisable(GL_SCISSOR_TEST);
	}

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
