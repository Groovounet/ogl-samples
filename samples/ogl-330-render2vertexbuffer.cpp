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
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken256-rgb8.dds");
	std::string const TEXTURE_HEIGHTMAP(glf::DATA_DIRECTORY + "heightmap.dds");
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


}//namespace

bool CMain::initTexture2D()
{
	stuff::mipmap2D<u8vec3> ColorMap = stuff::load2D<u8vec3>(TEXTURE_DIFFUSE);
	glGenTextures(1, &texture2DName);
	glBindTexture(GL_TEXTURE_2D, texture2DName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_NEAREST GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(ColorMap.width()), GLsizei(ColorMap.height()), 0, GL_BGR, GL_UNSIGNED_BYTE, &ColorMap[0]);

	stuff::mipmap2D<u8vec3> HeightMap = stuff::load2D<u8vec3>(TEXTURE_HEIGHT);
	glGenTextures(1, &heightmapName);
	glBindTexture(GL_TEXTURE_2D, heightmapName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_NEAREST GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(HeightMap.width()), GLsizei(HeightMap.height()), 0, GL_RGB, GL_UNSIGNED_BYTE, &HeightMap[0]);
	


	return true;
}

bool initSampler()
{

}

bool initTexture2D()
{
	glGenTextures(1, &Texture2DName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture2DName);

	// Set image
	gli::image Image = gli::import_as(TEXTURE_DIFFUSE);
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

	return glf::checkError("initTexture2D");
}

bool initProgram()
{
	bool Validated = true;
	
	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertexShaderName);
		glAttachShader(ProgramName, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);

		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	if(Validated)
	{
		glUseProgram(ProgramName);
		glUniform4fv(UniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
	}

	return Validated;
}

bool initArrayBuffer()
{
	heightmapWidth = GLsizei(HeightMap.width());
	heightmapHeight = GLsizei(HeightMap.height());

	for(GLint j = 0; j < heightmapHeight - 1; ++j)
	for(GLint i = 0; i < heightmapWidth - 1; ++i)
	{
		indexes.push_back((i + 0) + (j + 0) * heightmapWidth);
		indexes.push_back((i + 1) + (j + 0) * heightmapWidth);
		indexes.push_back((i + 1) + (j + 1) * heightmapWidth);
		indexes.push_back((i + 0) + (j + 0) * heightmapWidth);
		indexes.push_back((i + 1) + (j + 1) * heightmapWidth);
		indexes.push_back((i + 0) + (j + 1) * heightmapWidth);
	}

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), &indexes[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
	glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	bool Result = true;
	if(Result)
	{
		programName[PASS_BUFFER] = initProgram(VERTEX_SHADER_SOURCE1, FRAGMENT_SHADER_SOURCE1);
		programName[PASS_RENDER] = initProgram(VERTEX_SHADER_SOURCE2, FRAGMENT_SHADER_SOURCE2);
	}

	if(Result)
		Result = initTexture2D();
	
	glViewport(0, 0, windowSize.x, windowSize.y);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Result = Result && checkError("Begin");
	return Result;

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

	return Validated && glf::checkError("begin");
}

bool end()
{
	glDeleteBuffers(1, &indexBuffer);
	glDeleteProgram(programName[PASS_BUFFER]);
	glDeleteProgram(programName[PASS_RENDER]);
	glDeleteTextures(1, &texture2DName);
	glDeleteTextures(1, &heightmapName);

	glDeleteBuffers(1, &BufferName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

	return glf::checkError("end");
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Pass 1: create the vertex buffer
	{
		mat4 Projection = glm::ortho2D(0.f, 1.f, 0.f, 1.f);
		mat4 ModelView = glm::mat4(1.0f);

		glUseProgram(programName[PASS_BUFFER]);

		glViewport(0, 0, heightmapWidth, heightmapHeight);

		GLint MVP = glGetUniformLocation(programName[PASS_BUFFER], "MVP");
		glUniformMatrix4fv(MVP, 1, GL_FALSE, Projection * ModelView);

		GLint Sampler = glGetUniformLocation(programName[PASS_BUFFER], "DiffuseSampler");
		glUniform1i(Sampler, 0);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, heightmapName);

		GLuint Buffer = 0;
		glGenBuffers(1, &Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer);
		glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STREAM_DRAW);

		GLuint Attrib = glGetAttribLocation(programName[PASS_BUFFER], "Position");
		glVertexAttribPointer(Attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(Attrib);
			glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glDisableVertexAttribArray(Attrib);

		glDeleteBuffers(1, &Buffer);
	}

	// Pass 2: Read the buffer and render as geometry
	{
		mat4 Projection = glm::perspective(45.0f, float(windowSize.x) / windowSize.y, 0.1f, 100.0f);
		mat4 ModelView = glm::translate(0.0f, 0.0f, -tranlationCurrent.y);
		ModelView = glm::rotate(ModelView, rotationCurrent.y,-1.f, 0.f, 0.f);
		ModelView = glm::rotate(ModelView, rotationCurrent.x, 0.f, 0.f, 1.f);
		ModelView = glm::translate(ModelView, -0.5f,-0.5f,-0.5f);

		glUseProgram(programName[PASS_RENDER]);
		GLint MVP = glGetUniformLocation(programName[PASS_RENDER], "MVP");
		GLuint Attrib = glGetAttribLocation(programName[PASS_RENDER], "Position");

		glViewport(0, 0, windowSize.x, windowSize.y);
		glUniformMatrix4fv(MVP, 1, GL_FALSE, Projection * ModelView);

		GLuint Buffer = 0;
        glGenBuffers(1, &Buffer);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, Buffer);
        glBufferData(GL_PIXEL_PACK_BUFFER, heightmapWidth * heightmapHeight * sizeof(u8vec4), NULL, GL_DYNAMIC_DRAW);

		glReadBuffer(GL_BACK);
        glReadPixels(0, 0, heightmapWidth, heightmapHeight, GL_RGBA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

        glBindBuffer(GL_ARRAY_BUFFER, Buffer);
		glVertexAttribPointer(Attrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
/* We are not limited by unsigned byte type. However using larger types like float significantly increase memory bandwize needs.
		GLuint Buffer = 0;
        glGenBuffers(1, &Buffer);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, Buffer);
        glBufferData(GL_PIXEL_PACK_BUFFER, heightmapWidth * heightmapHeight * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);

		glReadBuffer(GL_BACK);
        glReadPixels(0, 0, heightmapWidth, heightmapHeight, GL_RGBA, GL_FLOAT, BUFFER_OFFSET(0));

        glBindBuffer(GL_ARRAY_BUFFER, Buffer);
		glVertexAttribPointer(Attrib, 4, GL_FLOAT, GL_TRUE, 0, 0);
*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		glEnableVertexAttribArray(Attrib);
			glDrawElements(GL_TRIANGLES, GLint(indexes.size()), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(Attrib);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &Buffer);
	}

	checkError("Render");
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
