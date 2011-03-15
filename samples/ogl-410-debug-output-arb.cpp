//**********************************
// OpenGL Debug output
// 02/08/2010 - 02/08/2010
//**********************************
// Christophe Riccio
// g.truc.creation@gmail.com
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include <glf/glf.hpp>

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Debug output";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/separate.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/separate.frag");
	std::string const TEXTURE_DIFFUSE_DXT5(glf::DATA_DIRECTORY + "kueken256-dxt5.dds");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 1;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 4;
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fv2f);
	glf::vertex_v2fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v2fv2f(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
	};

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLuint);
	GLuint const ElementData[ElementCount] =
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
			MAX
		};
	}//namespace buffer

	namespace program
	{
		enum type
		{
			VERTEX,
			FRAGMENT,
			MAX
		};
	}//namespace program

	GLuint PipelineName = 0;
	GLuint ProgramName[program::MAX];
	GLuint BufferName[buffer::MAX];
	GLuint VertexArrayName;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;
	GLuint Texture2DName = 0;

}//namespace

bool initDebugOutput()
{
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return glf::checkError("initDebugOutput");
}

bool initProgram()
{
	bool Validated = true;

	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);

	if(Validated)
	{
		std::string VertexSourceContent = glf::loadFile(VERTEX_SHADER_SOURCE);
		char const * VertexSourcePointer = VertexSourceContent.c_str();
		ProgramName[program::VERTEX] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &VertexSourcePointer);
		Validated = glf::checkProgram(ProgramName[program::VERTEX]);
	}

	if(Validated)
	{
		std::string FragmentSourceContent = glf::loadFile(FRAGMENT_SHADER_SOURCE);
		char const * FragmentSourcePointer = FragmentSourceContent.c_str();
		ProgramName[program::FRAGMENT] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &FragmentSourcePointer);
		Validated = glf::checkProgram(ProgramName[program::FRAGMENT]);
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName[program::VERTEX], "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName[program::FRAGMENT], "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initTexture2D()
{
	glGenTextures(1, &Texture2DName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture2DName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

	gli::texture2D Image = gli::load(TEXTURE_DIFFUSE_DXT5);
	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glCompressedTexImage2D(
			GL_TEXTURE_2D,
			GLint(Level),
			GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0, 
			GLsizei(Image[Level].capacity()), 
			Image[Level].data());
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return glf::checkError("initTexture2D");
}

bool initVertexBuffer()
{
	// Generate a buffer object
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_ARB_debug_output");

	if(Validated)
		Validated = initDebugOutput();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initVertexBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initTexture2D();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteTextures(1, &Texture2DName);
	glDeleteProgram(ProgramName[program::VERTEX]);
	glDeleteProgram(ProgramName[program::FRAGMENT]);
	glBindProgramPipeline(0);
	glDeleteProgramPipelines(1, &PipelineName);

	return glf::checkError("end");
}

void display()
{
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslateZ = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslateZ, float(Window.RotationCurrent.y), glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, float(Window.RotationCurrent.x), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 View = ViewRotateY;
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glProgramUniformMatrix4fv(ProgramName[program::VERTEX], UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform1i(ProgramName[program::FRAGMENT], UniformDiffuse, 0);

	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size.x, Window.Size.y)[0]);

	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glBindProgramPipeline(PipelineName);
	glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, ProgramName[program::VERTEX]);
	glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAGMENT]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture2DName);

	glBindVertexArray(5);//VertexArrayName);
	glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_INT, NULL, 1, 0);

	glBindProgramPipeline(0);

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
