//**********************************
// OpenGL Cube map
// 20/08/2010
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
	std::string const SAMPLE_NAME = "OpenGL Cube map";
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/texture-cube.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/texture-cube.frag");
	std::string const TEXTURE_DIFFUSE_POSX(glf::DATA_DIRECTORY + "posx.dds");
	std::string const TEXTURE_DIFFUSE_POSY(glf::DATA_DIRECTORY + "posy.dds");
	std::string const TEXTURE_DIFFUSE_POSZ(glf::DATA_DIRECTORY + "posz.dds");
	std::string const TEXTURE_DIFFUSE_NEGX(glf::DATA_DIRECTORY + "negx.dds");
	std::string const TEXTURE_DIFFUSE_NEGY(glf::DATA_DIRECTORY + "negy.dds");
	std::string const TEXTURE_DIFFUSE_NEGZ(glf::DATA_DIRECTORY + "negz.dds");

	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 3;
	int const SAMPLE_MINOR_VERSION = 3;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	// With DDS textures, v texture coordinate are reversed, from top to bottom
	GLsizei const VertexCount = 6;
	GLsizeiptr const VertexSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const VertexData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};

	GLuint VertexArrayName = 0;
	GLuint ProgramName = 0;

	GLuint BufferName = 0;
	GLuint TextureName = 0;
	GLuint SamplerName = 0;

	GLint UniformMV = 0;
	GLint UniformMVP = 0;
	GLint UniformEnvironment = 0;
	GLint UniformCamera = 0;

	glm::ivec4 Viewport;

}//namespace

bool initProgram()
{
	bool Validated = true;
	
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

	if(Validated)
	{
		UniformMV = glGetUniformLocation(ProgramName, "MV");
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformEnvironment = glGetUniformLocation(ProgramName, "Environment");
		UniformCamera = glGetUniformLocation(ProgramName, "Camera");
	}

	return glf::checkError("initProgram");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");;
}

void loadTextureFace(GLenum target, GLenum internalformat, std::string const & Filename)
{
	gli::texture2D Image = gli::load(Filename);
	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glCompressedTexImage2D(
			target,
			GLint(Level),
			internalformat,
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0, 
			GLsizei(Image[Level].capacity()), 
			Image[Level].data());
	}
}

bool initSampler()
{
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
	glSamplerParameterf(SamplerName, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

	return glf::checkError("initSampler");
}

bool initTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &TextureName);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureName);

	loadTextureFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, TEXTURE_DIFFUSE_POSX);
	loadTextureFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, TEXTURE_DIFFUSE_NEGX);
	loadTextureFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, TEXTURE_DIFFUSE_POSY);
	loadTextureFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, TEXTURE_DIFFUSE_NEGY);
	loadTextureFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, TEXTURE_DIFFUSE_POSZ);
	loadTextureFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, TEXTURE_DIFFUSE_NEGZ);

	return glf::checkError("initTexture2D");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
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
		Validated = initVertexArray();
	if(Validated)
		Validated = initTexture();
	if(Validated)
		Validated = initSampler();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName);
	glDeleteTextures(1, &TextureName);
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
	glm::mat4 MV = View * Model;

	glViewport(0, 0, Window.Size.x, Window.Size.y);
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the program for use
	glUseProgram(ProgramName);
	glUniformMatrix4fv(UniformMV, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(UniformEnvironment, 0);
	glUniform3fv(UniformCamera, 1, &glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y)[0]);

	glBindVertexArray(VertexArrayName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureName);
	glBindSampler(0, SamplerName);

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
