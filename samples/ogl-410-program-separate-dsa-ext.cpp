//**********************************
// OpenGL Separate program
// 02/08/2010 - 02/08/2010
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
	std::string const SAMPLE_NAME = "OpenGL Separate program DSA";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/separate.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "410/separate.frag");
	std::string const TEXTURE_DIFFUSE_DXT5(glf::DATA_DIRECTORY + "kueken256-dxt5.dds");
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


	GLuint PipelineName(0);
	GLuint SeparateProgramName[program::MAX];
	GLint SeparateUniformMVP(0);
	GLint SeparateUniformDiffuse(0);
	
	GLuint UnifiedProgramName;
	GLint UnifiedUniformMVP(0);
	GLint UnifiedUniformDiffuse(0);

	GLuint BufferName[buffer::MAX];
	GLuint VertexArrayName;
	GLuint Texture2DName(0);

}//namespace

bool initUnifiedProgram()
{
	bool Validated = true;

	// Create program
	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		UnifiedProgramName = glCreateProgram();
		glAttachShader(UnifiedProgramName, VertShaderName);
		glAttachShader(UnifiedProgramName, FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);
		glLinkProgram(UnifiedProgramName);
		Validated = Validated && glf::checkProgram(UnifiedProgramName);
	}

	if(Validated)
	{
		UnifiedUniformMVP = glGetUniformLocation(UnifiedProgramName, "MVP");
		UnifiedUniformDiffuse = glGetUniformLocation(UnifiedProgramName, "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initSeparateProgram()
{
	bool Validated = true;

	glGenProgramPipelines(1, &PipelineName);

	if(Validated)
	{
		std::string VertexSourceContent = glf::loadFile(VERTEX_SHADER_SOURCE);
		char const * VertexSourcePointer = VertexSourceContent.c_str();
		SeparateProgramName[program::VERTEX] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &VertexSourcePointer);
		Validated = glf::checkProgram(SeparateProgramName[program::VERTEX]);
	}

	if(Validated)
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, SeparateProgramName[program::VERTEX]);

	if(Validated)
	{
		std::string FragmentSourceContent = glf::loadFile(FRAGMENT_SHADER_SOURCE);
		char const * FragmentSourcePointer = FragmentSourceContent.c_str();
		SeparateProgramName[program::FRAGMENT] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &FragmentSourcePointer);
		Validated = glf::checkProgram(SeparateProgramName[program::FRAGMENT]);
	}

	if(Validated)
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, SeparateProgramName[program::FRAGMENT]);

	// Get variables locations
	if(Validated)
	{
		SeparateUniformMVP = glGetUniformLocation(SeparateProgramName[program::VERTEX], "MVP");
		SeparateUniformDiffuse = glGetUniformLocation(SeparateProgramName[program::FRAGMENT], "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initTexture2D()
{
	glGenTextures(1, &Texture2DName);
	glTextureParameteriEXT(Texture2DName, GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTextureParameteriEXT(Texture2DName, GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
	glTextureParameteriEXT(Texture2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTextureParameteriEXT(Texture2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTextureParameteriEXT(Texture2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTextureParameteriEXT(Texture2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

	gli::texture2D Image = gli::load(TEXTURE_DIFFUSE_DXT5);
	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glCompressedTextureImage2DEXT(
			Texture2DName,
			GL_TEXTURE_2D,
			GLint(Level),
			GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0, 
			GLsizei(Image[Level].capacity()), 
			Image[Level].data());
	}

	return glf::checkError("initTexture2D");
}

bool initVertexBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);
	glNamedBufferDataEXT(BufferName[buffer::VERTEX], VertexSize, VertexData, GL_STATIC_DRAW);
	glNamedBufferDataEXT(BufferName[buffer::ELEMENT], ElementSize, ElementData, GL_STATIC_DRAW);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName[buffer::VERTEX], 
		glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName[buffer::VERTEX], 
		glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), sizeof(glm::vec2));

	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::TEXCOORD);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_EXT_direct_state_access");

	if(Validated)
		Validated = initSeparateProgram();
	if(Validated)
		Validated = initUnifiedProgram();
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
	glDeleteProgram(SeparateProgramName[program::VERTEX]);
	glDeleteProgram(SeparateProgramName[program::FRAGMENT]);
	glDeleteProgram(UnifiedProgramName);
	glDeleteProgramPipelines(1, &PipelineName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
    glm::mat4 Projection = glm::perspective(45.0f, 2.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslateZ = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslateZ, float(Window.RotationCurrent.y), glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, float(Window.RotationCurrent.x), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 View = ViewRotateY;
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, Texture2DName);
	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);

	// Render with the separate programs
	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size.x / 2, Window.Size.y)[0]);
	glProgramUniformMatrix4fv(SeparateProgramName[program::VERTEX], SeparateUniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform1i(SeparateProgramName[program::FRAGMENT], SeparateUniformDiffuse, 0);
	glBindProgramPipeline(PipelineName);
		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_INT, NULL, 1, 0);
	glBindProgramPipeline(0);

	// Render with the unified programs
	glViewportIndexedfv(0, &glm::vec4(Window.Size.x / 2, 0, Window.Size.x / 2, Window.Size.y)[0]);
	glProgramUniformMatrix4fv(UnifiedProgramName, UnifiedUniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform1i(UnifiedProgramName, UnifiedUniformDiffuse, 0);
	glUseProgram(UnifiedProgramName);
		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_INT, NULL, 1, 0);
	glUseProgram(0);

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
