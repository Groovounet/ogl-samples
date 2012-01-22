//**********************************
// OpenGL Multi draw indirect
// 22/06/2011 - 08/10/2011
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
	std::string const SAMPLE_NAME = "OpenGL Multi draw indirect";
	std::string const VERTEX_SHADER_SOURCE(glf::DATA_DIRECTORY + "ogl-420/draw-indirect.vert");
	std::string const FRAGMENT_SHADER_SOURCE(glf::DATA_DIRECTORY + "ogl-420/draw-indirect.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(glm::uint32);
	glm::uint32 const ElementData[ElementCount] =
	{
		0, 1, 2,
		0, 2, 3
	};

	GLsizei const VertexCount(8);
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec4);
	glm::vec4 const PositionData[VertexCount] =
	{
		glm::vec4(-1.0f,-1.0f, 0.5f, 1.0f),
		glm::vec4( 1.0f,-1.0f, 0.5f, 1.0f),
		glm::vec4( 1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 0.5f, 1.0f),
		glm::vec4(-0.5f,-1.0f,-0.5f, 1.0f),
		glm::vec4( 0.5f,-1.0f,-0.5f, 1.0f),
		glm::vec4( 1.5f, 1.0f,-0.5f, 1.0f),
		glm::vec4(-1.5f, 1.0f,-0.5f, 1.0f)
	};

	namespace buffer
	{
		enum type
		{
			VERTEX,
			ELEMENT,
			TRANSFORM,
			INDIRECT,
			MAX
		};
	}//namespace buffer

    struct DrawArraysIndirectCommand
	{
		GLuint count;
		GLuint primCount;
		GLuint first;
		GLuint baseInstance;
    };

    struct DrawElementsIndirectCommand
	{
		GLuint count;
		GLuint primCount;
		GLuint firstIndex;
		GLint  baseVertex;
		GLuint baseInstance;
    };

	GLuint VertexArrayName(0);
	GLuint PipelineName(0);
	GLuint ProgramName(0);
	GLuint BufferName[buffer::MAX];

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);
	glBindProgramPipeline(0);

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);

		ProgramName = glCreateProgram();
		glProgramParameteri(ProgramName, GL_PROGRAM_SEPARABLE, GL_TRUE);
		glAttachShader(ProgramName, VertShaderName);
		glAttachShader(ProgramName, FragShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(FragShaderName);
		glLinkProgram(ProgramName);
		Validated = glf::checkProgram(ProgramName);
	}

	glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT, ProgramName);

	return Validated && glf::checkError("initProgram");
}

bool initBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);	

	DrawElementsIndirectCommand Command[2];
	Command[0].count = ElementCount;
	Command[0].primCount = 1;
	Command[0].firstIndex = 0;
	Command[0].baseVertex = 0;
	Command[0].baseInstance = 0;
	Command[1].count = ElementCount;
	Command[1].primCount = 1;
	Command[1].firstIndex = 0;
	Command[1].baseVertex = 4;
	Command[1].baseInstance = 0;

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, BufferName[buffer::INDIRECT]);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(Command), Command, GL_STATIC_READ);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
			glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
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
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_AMD_multi_draw_indirect");

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initBuffer();
	if(Validated)
		Validated = initVertexArray();
	return Validated && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteProgramPipelines(1, &PipelineName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

	return glf::checkError("end");
}

void display()
{
	{
		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
		glm::mat4* Pointer = (glm::mat4*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), 
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;

		*Pointer = MVP;
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}

	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size.x, Window.Size.y)[0]);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f)[0]);

	glBindProgramPipeline(PipelineName);
	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]); //!\ Need to be called after glBindVertexArray...
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, BufferName[buffer::INDIRECT]);
	glMultiDrawElementsIndirectAMD(GL_TRIANGLES, GL_UNSIGNED_INT, 0, 2, sizeof(DrawElementsIndirectCommand));

	glf::checkError("display");
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
