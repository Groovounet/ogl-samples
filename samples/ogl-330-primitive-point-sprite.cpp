//**********************************
// OpenGL Samples Pack
// ogl-samples.g-truc.net
//**********************************
// OpenGL Point
// 18/07/2011 - 18/07/2011
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
	std::string const SAMPLE_NAME = "OpenGL Point";
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/point.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "330/point.frag");
	std::string const TEXTURE_DIFFUSE(glf::DATA_DIRECTORY + "kueken256-rgba8.dds");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(3);
	int const SAMPLE_MINOR_VERSION(3);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fc4f);
	glf::vertex_v2fc4f const VertexData[VertexCount] =
	{
		glf::vertex_v2fc4f(glm::vec2(-1.0f,-1.0f), glm::vec4(1, 0, 0, 1)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f,-1.0f), glm::vec4(1, 1, 0, 1)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f, 1.0f), glm::vec4(0, 1, 0, 1)),
		glf::vertex_v2fc4f(glm::vec2(-1.0f, 1.0f), glm::vec4(0, 0, 1, 1))
	};

	GLuint VertexArrayName(0);
	GLuint ProgramName(0);
	GLuint BufferName(0);
	GLuint TextureName(0);
	GLint UniformMVP(0);
	GLint UniformMV(0);
	GLint UniformDiffuse(0);

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	// Create program
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

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformMV = glGetUniformLocation(ProgramName, "MV");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

// Buffer update using glBufferSubData
bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &BufferName);

	// Bind the buffer for use
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);

	// Reserve buffer memory but don't copy the values
    glBufferData(GL_ARRAY_BUFFER, VertexSize, NULL, GL_STATIC_DRAW);

	// Copy the vertex data in the buffer, in this sample for the whole range of data.
    glBufferSubData(GL_ARRAY_BUFFER, 0, VertexSize, &VertexData[0]);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initTexture2D()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &TextureName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set image
	gli::texture2D Image = gli::load(TEXTURE_DIFFUSE);
	for(std::size_t Level = 0; Level < Image.levels(); ++Level)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			GL_RGBA8, 
			GLsizei(Image[Level].dimensions().x), 
			GLsizei(Image[Level].dimensions().y), 
			0,  
			GL_BGRA, 
			GL_UNSIGNED_BYTE, 
			Image[Level].data());
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return glf::checkError("initTexture2D");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_ARB_viewport_array");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
	//glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
	
	if(Validated)
		Validated = initTexture2D();
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
	// Delete objects
	glDeleteBuffers(1, &BufferName);
	glDeleteTextures(1, &TextureName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

	return glf::checkError("end");
}

void display()
{
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;
	glm::mat4 MV = View * Model;

	glProgramUniformMatrix4fv(ProgramName, UniformMV, 1, GL_FALSE, &MV[0][0]);
	glProgramUniformMatrix4fv(ProgramName, UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	float Depth(1.0f);
	glViewportIndexedf(0, 0, 0, float(Window.Size.x), float(Window.Size.y));
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
	glClearBufferfv(GL_DEPTH, 0, &Depth);

	glEnable(GL_SCISSOR_TEST);
	glScissor(Window.Size.x / 4, Window.Size.y / 4, Window.Size.x / 2, Window.Size.y / 2);

	glViewportIndexedf(0, float(Window.Size.x) * 0.25f, float(Window.Size.y) * 0.25f, float(Window.Size.x) * 0.5f, float(Window.Size.y) * 0.5f);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f)[0]);
	glClearBufferfv(GL_DEPTH, 0, &Depth);

	glDisable(GL_SCISSOR_TEST);

	glUseProgram(ProgramName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName);
	glBindVertexArray(VertexArrayName);

	glDrawArraysInstanced(GL_POINTS, 0, VertexCount, 1);

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
