//**********************************\\
// Render to vertex buffer			\\
//**********************************\\
// OpenGL 2.1						\\
//**********************************\\
// 13/12/2008 - Christophe Riccio	\\
// G-Truc Creation - www.g-truc.net \\
//**********************************\\

#include "main.h"
#include "image/loader.hpp"
#include <vector>

namespace glm
{
    using GLM_GTX_transform;
    using GLM_GTX_matrix_projection;
    using GLM_GTX_number_precision;
}

namespace
{
	const char* TITLE = "Render to vertex buffer, OpenGL 2.1";

	std::string loadFile(const char* Filename)
	{
		std::ifstream stream(Filename, std::ios::in);

		if(!stream.is_open())
			return "";

		std::string Line = "";
		std::string Text = "";

		while(getline(stream, Line))
    		Text += "\n" + Line;

		stream.close();

		return Text;
	}

	bool checkError(const char* Title)
	{
	    int Error;
	    if((Error = glGetError()) != GL_NO_ERROR)
	    {
		    const char* Message = (const char*)gluErrorString(Error);
            fprintf(stdout, "OpenGL Error(%s): %s\n", Title, Message);
	    }

		return Error == GL_NO_ERROR;
	}

	const GLsizei VertexCount = 6;

	const GLsizeiptr PositionSize = VertexCount * sizeof(vec2);
	const vec2 PositionData[VertexCount] =
	{
		vec2(-1.0f,-1.0f),
		vec2( 1.0f,-1.0f),
		vec2( 1.0f, 1.0f),
		vec2( 1.0f, 1.0f),
		vec2(-1.0f, 1.0f),
		vec2(-1.0f,-1.0f)
	};

	const GLsizeiptr TexcoordSize = VertexCount * sizeof(vec2);
	const vec2 TexcoordData[] =
	{
		 vec2(0.0f, 0.0f),
		 vec2(1.0f, 0.0f),
		 vec2(1.0f, 1.0f),
		 vec2(1.0f, 1.0f),
		 vec2(0.0f, 1.0f),
		 vec2(0.0f, 0.0f)
	};

	const char* VERTEX_SHADER_SOURCE1 = "./data/shader.vert";
	const char* FRAGMENT_SHADER_SOURCE1 = "./data/shader.frag";
	const char* VERTEX_SHADER_SOURCE2 = "./data/shader2.vert";
	const char* FRAGMENT_SHADER_SOURCE2 = "./data/shader2.frag";
	const char* TEXTURE_DIFFUSE = "./data/diffuse.tga";
	const char* TEXTURE_HEIGHT = "./data/heightmap.tga";
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

CMain::CMain()
{
	title = TITLE;
}

CMain::~CMain()
{}

bool CMain::Begin(const ivec2& WindowSize)
{
	windowSize = WindowSize;

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
}

bool CMain::End()
{
	glDeleteBuffers(1, &indexBuffer);
	glDeleteProgram(programName[PASS_BUFFER]);
	glDeleteProgram(programName[PASS_RENDER]);
	glDeleteTextures(1, &texture2DName);
	glDeleteTextures(1, &heightmapName);
	
	return checkError("End");
}

void CMain::Render()
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

GLuint CMain::initProgram(const char* VertexShader, const char* FragmentShader)
{
	GLuint VertexShaderName = 0;

	fprintf(stdout, "Compiling shader...\n");

	// Compile a shader
	bool Success = true;
	if(Success)
	{
		std::string VertexSource0 = loadFile(VertexShader);
		const char* VertexSource = VertexSource0.c_str();
		VertexShaderName = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderName, 1, &VertexSource, NULL);
		glCompileShader(VertexShaderName);
	}

	// Check compiling
	if(VertexShaderName)
	{
		GLint Result = GL_FALSE;
		glGetShaderiv(VertexShaderName, GL_COMPILE_STATUS, &Result);
		if(Result == GL_FALSE)
			Success = false;
		fprintf(stdout, "%s\n", VertexShader);
        int InfoLogLength;
        glGetShaderiv(VertexShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> Buffer(InfoLogLength);
		glGetShaderInfoLog(VertexShaderName, InfoLogLength, NULL, &Buffer[0]);
		if(InfoLogLength > 1)
			fprintf(stdout, "%s\n", &Buffer[0]);
	}

	GLuint FragmentShaderName = 0;

	// Compile a shader
	if(Success)
	{
		std::string Source0 = loadFile(FragmentShader);
		const char* Source = Source0.c_str();
		FragmentShaderName = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderName, 1, &Source, NULL);
		glCompileShader(FragmentShaderName);
	}

	// Check compiling
	if(FragmentShaderName)
	{
		GLint Result = GL_FALSE;
		glGetShaderiv(FragmentShaderName, GL_COMPILE_STATUS, &Result);
		if(Result == GL_FALSE)
			Success = false;
		fprintf(stdout, "%s\n", FragmentShader);
        int InfoLogLength;
        glGetShaderiv(FragmentShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> Buffer(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderName, InfoLogLength, NULL, &Buffer[0]);
		if(InfoLogLength > 1)
			fprintf(stdout, "%s\n", &Buffer[0]);
	}

	// Link a program
	GLuint ProgramName = 0;
	if(Success)
	{
		ProgramName = glCreateProgram();
		glAttachShader(ProgramName, VertexShaderName);
		glDeleteShader(VertexShaderName);
		glAttachShader(ProgramName, FragmentShaderName);
		glDeleteShader(FragmentShaderName);
		glLinkProgram(ProgramName);
	}

	fprintf(stdout, "\nLinking program...\n");

	// Check linking
	if(ProgramName)
	{
		GLint Result = GL_FALSE;
		glGetProgramiv(ProgramName, GL_LINK_STATUS, &Result);
		if(Result == GL_FALSE)
			Success = false;

        int InfoLogLength;
        glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> Buffer(InfoLogLength);
		glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
		if(InfoLogLength > 1)
			fprintf(stdout, "%s\n", &Buffer[0]);
	}

	return ProgramName;
}

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
