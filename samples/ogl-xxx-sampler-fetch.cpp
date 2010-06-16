//**********************************
// OpenGL Programmable trilinear filtering
// 27/05/2010
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
	std::string const SAMPLE_NAME = "OpenGL Programmable trilinear filtering";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "xxx/fetch.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "xxx/fetch.frag");
	std::string const TEXTURE_DIFFUSE_DXT5(glf::DATA_DIRECTORY + "kueken256-dxt5.dds");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 0;

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
	GLsizei const VertexCount = 6;
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

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	namespace viewport
	{
		enum type
		{
			V00,
			V10,
			V11,
			V01,
			MAX
		};
	}//namespace viewport

	GLuint VertexArrayName = 0;
	GLuint ProgramName = 0;

	GLuint BufferName = 0;
	GLuint Image2DName = 0;
	GLuint SamplerName = 0;

	GLuint UniformMVP = 0;
	GLuint UniformDiffuse = 0;

	GLenum SwizzleR[viewport::MAX];
	GLenum SwizzleG[viewport::MAX];
	GLenum SwizzleB[viewport::MAX];
	GLenum SwizzleA[viewport::MAX];
	glm::ivec4 Viewport[viewport::MAX];
}//namespace

bool initProgram()
{
	bool Validated = true;

	// Create program
	if(Validated)
	{
		ProgramName = glCreateProgram();

		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		glAttachShader(ProgramName, VertexShaderName);
		glDeleteShader(VertexShaderName);

		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);
		glAttachShader(ProgramName, FragmentShaderName);
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

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);
    glNamedBufferDataEXT(BufferName, VertexSize, VertexData, GL_STATIC_DRAW);

	return glf::checkError("initArrayBuffer");;
}

bool initTexture2D()
{
	glGenTextures(1, &Image2DName);

	glTextureParameteriEXT(Image2DName, GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTextureParameteriEXT(Image2DName, GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
	glTextureParameteriEXT(Image2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
	glTextureParameteriEXT(Image2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
	glTextureParameteriEXT(Image2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
	glTextureParameteriEXT(Image2DName, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

	gli::image Image = gli::import_as(TEXTURE_DIFFUSE_DXT5);
	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glCompressedTextureImage2DEXT(
			Image2DName,
			GL_TEXTURE_2D,
			GLint(Level),
			GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0, 
			Image[Level].capacity(), 
			Image[Level].data());
	}

	return glf::checkError("initTexture2D");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName, glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexArrayVertexAttribOffsetEXT(VertexArrayName, BufferName, glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), sizeof(glm::vec2));

	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::POSITION);
	glEnableVertexArrayAttribEXT(VertexArrayName, glf::semantic::attr::TEXCOORD);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	// Check the OpenGL version
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Validated = glf::version(MajorVersion, MinorVersion) >= glf::version(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initTexture2D();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName);
	glDeleteTextures(1, &Image2DName);
	glDeleteSamplers(1, &SamplerName);
	glDeleteVertexArrays(1, &VertexArrayName);

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

	glProgramUniformMatrix4fvEXT(ProgramName, UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform1iEXT(ProgramName, UniformDiffuse, 0);

	glViewport(0, 0, Window.Size.x, Window.Size.y);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glUseProgram(ProgramName);

	glViewport(0, 0, Window.Size.x, Window.Size.y);

	glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, Image2DName);
	glBindVertexArray(VertexArrayName);

	glDrawArrays(GL_TRIANGLES, 0, VertexCount);

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
