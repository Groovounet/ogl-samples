//**********************************
// OpenGL Double
// 28/06/2010 - 28/06/2010
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
	std::string const SAMPLE_NAME = "OpenGL Double";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/double.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "400/double.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 4;
	int const SAMPLE_MINOR_VERSION = 0;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 6;
	GLsizeiptr const PositionSizeF16 = VertexCount * sizeof(glm::hvec2);
	glm::hvec2 const PositionDataF16[VertexCount] =
	{
		glm::hvec2(-1.0f, -1.0f),
		glm::hvec2( 1.0f, -1.0f),
		glm::hvec2( 1.0f,  1.0f),
		glm::hvec2(-1.0f,  1.0f)
	};

	GLsizeiptr const PositionSizeF32 = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionDataF32[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f)
	};

	GLsizeiptr const PositionSizeI8 = VertexCount * sizeof(glm::i8vec2);
	glm::i8vec2 const PositionDataI8[VertexCount] =
	{
		glm::i8vec2(-1,-1),
		glm::i8vec2( 1,-1),
		glm::i8vec2( 1, 1),
		glm::i8vec2(-1, 1)
	};

	GLsizeiptr const PositionSizeI32 = VertexCount * sizeof(glm::i32vec2);
	glm::i32vec2 const PositionDataI32[VertexCount] =
	{
		glm::i32vec2(-1,-1),
		glm::i32vec2( 1,-1),
		glm::i32vec2( 1, 1),
		glm::i32vec2(-1, 1)
	};

	GLsizei const ElementCount = 6;
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace buffer
	{
		enum type
		{
			F16,
			F32,
			I8,
			I32,
			ELEMENT,
			MAX
		};
	}//namespace buffer

	GLuint ProgramName = 0;
	GLuint BufferName[buffer::MAX];
	GLuint VertexArrayName[buffer::MAX];
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;
	glm::ivec4 Viewport[buffer::MAX];

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	// Create program
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

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName, "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexBuffer()
{
	// Generate a buffer object
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Allocate and copy buffers memory
    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F16]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeF16, PositionDataF16, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F32]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeF32, PositionDataF32, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::I8]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeI8, PositionDataI8, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::I32]);
    glBufferData(GL_ARRAY_BUFFER, PositionSizeI32, PositionDataI32, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(buffer::MAX, VertexArrayName);

    glBindVertexArray(VertexArrayName[buffer::F16]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F16]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_HALF_FLOAT, GL_FALSE, sizeof(glm::hvec2), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBindVertexArray(0);

    glBindVertexArray(VertexArrayName[buffer::F32]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F32]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBindVertexArray(0);

    glBindVertexArray(VertexArrayName[buffer::I8]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::I8]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_BYTE, GL_FALSE, sizeof(glm::u8vec2), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBindVertexArray(0);

    glBindVertexArray(VertexArrayName[buffer::I32]);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::I32]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_INT, GL_FALSE, sizeof(glm::i32vec2), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool begin()
{
	Viewport[buffer::F16] = glm::ivec4(0, 0, Window.Size >> 1);
	Viewport[buffer::F32] = glm::ivec4(Window.Size.x >> 1, 0, Window.Size >> 1);
	Viewport[buffer::I8]  = glm::ivec4(Window.Size.x >> 1, Window.Size.y >> 1, Window.Size >> 1);
	Viewport[buffer::I32] = glm::ivec4(0, Window.Size.y >> 1, Window.Size >> 1);

	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Validated = (MajorVersion * 10 + MinorVersion) >= (SAMPLE_MAJOR_VERSION * 10 + SAMPLE_MINOR_VERSION);
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initVertexBuffer();
	if(Validated)
		Validated = initVertexArray();

	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteVertexArrays(buffer::MAX, VertexArrayName);
	glDeleteProgram(ProgramName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
    glm::dmat4 Projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
	glm::dmat4 ViewTranslateZ = glm::translate(glm::dmat4(1.0), glm::dvec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::dmat4 ViewRotateX = glm::rotate(ViewTranslateZ, double(Window.RotationCurrent.y), glm::dvec3(1.f, 0.f, 0.f));
	glm::dmat4 ViewRotateY = glm::rotate(ViewRotateX, double(Window.RotationCurrent.x), glm::dvec3(0.f, 1.f, 0.f));
	glm::dmat4 View = ViewRotateY;
	glm::dmat4 Model = glm::dmat4(1.0f);
	glm::dmat4 MVP = Projection * View * Model;

	// Clear color buffer with black
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	// Bind program
	glUseProgram(ProgramName);

	glUniformMatrix4dv(UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform4dv(UniformDiffuse, 1, &glm::dvec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	for(std::size_t Index = 0; Index < buffer::MAX; ++Index)
	{
		// Set the display viewport
		glViewport(
			Viewport[Index].x, 
			Viewport[Index].y, 
			Viewport[Index].z, 
			Viewport[Index].w);

		glBindVertexArray(VertexArrayName[Index]);
		glDrawArrays(GL_TRIANGLES, 0, VertexCount);
	}

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
