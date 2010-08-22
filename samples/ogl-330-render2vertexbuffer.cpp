//**********************************
// OpenGL Render to vertex buffer
// 13/12/2008 - 19/08/2010
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
	std::string const SAMPLE_NAME = "OpenGL Viewport";
	std::string const VERT_SHADER_SOURCE1(glf::DATA_DIRECTORY + "330/r2vb1.vert");
	std::string const FRAG_SHADER_SOURCE1(glf::DATA_DIRECTORY + "330/r2vb1.frag");
	std::string const VERT_SHADER_SOURCE2(glf::DATA_DIRECTORY + "330/r2vb2.vert");
	std::string const FRAG_SHADER_SOURCE2(glf::DATA_DIRECTORY + "330/r2vb2.frag");
	std::string const TEXTURE_DIFFUSE_SOURCE(glf::DATA_DIRECTORY + "kueken256-rgb8.dds");
	std::string const TEXTURE_HEIGHTMAP_SOURCE(glf::DATA_DIRECTORY + "heightmap.dds");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 3;
	int const SAMPLE_MINOR_VERSION = 3;

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

	enum texture
	{
		TEXTURE_DIFFUSE,
		TEXTURE_HEIGHTMAP,
		TEXTURE_MAX
	};

	enum buffer
	{
		BUFFER_VERTEX,
		BUFFER_ELEMENT,
		BUFFER_STREAM,
		BUFFER_MAX
	};

	enum program
	{
		PROGRAM_PASS1,
		PROGRAM_PASS2,
		PROGRAM_MAX
	};

	GLuint ProgramName[PROGRAM_MAX] = {0, 0};
	GLuint UniformMVP[PROGRAM_MAX] = {0, 0};
	GLuint UniformDiffuse[PROGRAM_MAX] = {0, 0};
	GLuint VertexArrayName[PROGRAM_MAX] = {0, 0};
	GLuint BufferName[BUFFER_MAX];
	GLuint TextureName[TEXTURE_MAX];
	glm::ivec2 HeightMapSize(0);

}//namespace

bool initSampler()
{

	return glf::checkError("initSampler");
}

bool initTexture()
{
	glGenTextures(TEXTURE_MAX, TextureName);
	glBindTexture(GL_TEXTURE_2D, TextureName[TEXTURE_DIFFUSE]);

	gli::image ImageDiffuse = gli::import_as(TEXTURE_DIFFUSE_SOURCE);
	for(std::size_t Level = 0; Level < ImageDiffuse.levels(); ++Level)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGB, 
			GLsizei(ImageDiffuse[Level].dimensions().x), 
			GLsizei(ImageDiffuse[Level].dimensions().y), 
			0,  
			GL_BGR, 
			GL_UNSIGNED_BYTE, 
			ImageDiffuse[Level].data());
	}

	glBindTexture(GL_TEXTURE_2D, TextureName[TEXTURE_HEIGHTMAP]);

	gli::image HeightMap = gli::import_as(TEXTURE_HEIGHTMAP_SOURCE);
	for(std::size_t Level = 0; Level < HeightMap.levels(); ++Level)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGB, 
			GLsizei(HeightMap[Level].dimensions().x), 
			GLsizei(HeightMap[Level].dimensions().y), 
			0,  
			GL_BGR, 
			GL_UNSIGNED_BYTE, 
			HeightMap[Level].data());
	}
	HeightMapSize = glm::ivec2(HeightMap[0].dimensions());

	return glf::checkError("initTexture");
}

bool initProgram()
{
	bool Validated = true;
	
	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE1);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE1);

		ProgramName[PROGRAM_PASS1] = glCreateProgram();
		glAttachShader(ProgramName[PROGRAM_PASS1], VertShaderName);
		glAttachShader(ProgramName[PROGRAM_PASS1], FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		glLinkProgram(ProgramName[PROGRAM_PASS1]);
		Validated = glf::checkProgram(ProgramName[PROGRAM_PASS1]);
	}

	if(Validated)
	{
		UniformMVP[PROGRAM_PASS1] = glGetUniformLocation(ProgramName[PROGRAM_PASS1], "MVP");
		UniformDiffuse[PROGRAM_PASS1] = glGetUniformLocation(ProgramName[PROGRAM_PASS1], "Diffuse");
	}

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE2);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE2);

		ProgramName[PROGRAM_PASS2] = glCreateProgram();
		glAttachShader(ProgramName[PROGRAM_PASS2], VertShaderName);
		glAttachShader(ProgramName[PROGRAM_PASS2], FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);

		glLinkProgram(ProgramName[PROGRAM_PASS2]);
		Validated = glf::checkProgram(ProgramName[PROGRAM_PASS2]);
	}

	if(Validated)
	{
		UniformMVP[PROGRAM_PASS2] = glGetUniformLocation(ProgramName[PROGRAM_PASS2], "MVP");
		UniformDiffuse[PROGRAM_PASS2] = glGetUniformLocation(ProgramName[PROGRAM_PASS2], "Diffuse");
	}

	return Validated;
}

bool initArrayBuffer()
{
    glGenBuffers(BUFFER_MAX, BufferName);

	std::vector<GLuint> Indexes;

	for(GLint j = 0; j < HeightMapSize.y - 1; ++j)
	for(GLint i = 0; i < HeightMapSize.x - 1; ++i)
	{
		Indexes.push_back((i + 0) + (j + 0) * HeightMapSize.x);
		Indexes.push_back((i + 1) + (j + 0) * HeightMapSize.x);
		Indexes.push_back((i + 1) + (j + 1) * HeightMapSize.x);
		Indexes.push_back((i + 0) + (j + 0) * HeightMapSize.x);
		Indexes.push_back((i + 1) + (j + 1) * HeightMapSize.x);
		Indexes.push_back((i + 0) + (j + 1) * HeightMapSize.x);
	}

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[BUFFER_ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indexes.size() * sizeof(unsigned int), &Indexes[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName[PROGRAM_PASS1]);
	glBindVertexArray(VertexArrayName[PROGRAM_PASS1]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_VERTEX]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VertexArrayName[PROGRAM_PASS2]);
	glBindVertexArray(VertexArrayName[PROGRAM_PASS2]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[BUFFER_STREAM]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
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
	bool Validated = (MajorVersion * 10 + MinorVersion) >= (SAMPLE_MAJOR_VERSION * 10 + SAMPLE_MINOR_VERSION);

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
	glDeleteProgram(ProgramName[PROGRAM_PASS1]);
	glDeleteProgram(ProgramName[PROGRAM_PASS2]);
	glDeleteTextures(TEXTURE_MAX, TextureName);
	glDeleteBuffers(BUFFER_MAX, BufferName);
	glDeleteVertexArrays(PROGRAM_MAX, VertexArrayName);

	return glf::checkError("end");
}

void display()
{
	glViewport(0, 0, Window.Size.x, Window.Size.y);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Pass 1: create the vertex buffer
	{
		glm::mat4 Projection = glm::ortho(0.f, 1.f, 0.f, 1.f);

		glUseProgram(ProgramName[PROGRAM_PASS1]);
		glUniform1i(UniformDiffuse[PROGRAM_PASS1], 0);
		glUniformMatrix4fv(UniformMVP[PROGRAM_PASS1], 1, GL_FALSE, &Projection[0][0]);

		glViewport(0, 0, HeightMapSize.x, HeightMapSize.y);
	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureName[TEXTURE_HEIGHTMAP]);

		glBindVertexArray(VertexArrayName[PROGRAM_PASS1]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[BUFFER_ELEMENT]);
		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1, 0);
	}

	// Pass 2: Read the buffer and render as geometry
	{
		// Compute the MVP (Model View Projection matrix)
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		glViewport(0, 0, Window.Size.x, Window.Size.y);

		glUseProgram(ProgramName[PROGRAM_PASS2]);
		glUniformMatrix4fv(UniformMVP[PROGRAM_PASS2], 1, GL_FALSE, &MVP[0][0]);

        glBindBuffer(GL_PIXEL_PACK_BUFFER, BufferName[BUFFER_STREAM]);
		glBufferData(GL_PIXEL_PACK_BUFFER, HeightMapSize.x * HeightMapSize.y * sizeof(glm::u8vec4), NULL, GL_DYNAMIC_DRAW);

		glReadBuffer(GL_BACK);
        glReadPixels(0, 0, HeightMapSize.x, HeightMapSize.y, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		glBindVertexArray(VertexArrayName[PROGRAM_PASS2]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[BUFFER_ELEMENT]);

		glDrawElements(GL_TRIANGLES, GLint(HeightMapSize.x * HeightMapSize.y), GL_UNSIGNED_INT, 0);
	}

	glf::checkError("display");
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
