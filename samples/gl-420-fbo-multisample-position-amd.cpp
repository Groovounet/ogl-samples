//**********************************
// OpenGL Sample Position
// 18/04/2011 - 23/02/2012
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
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY +"gl-420/multi-draw-indirect.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "gl-420/multi-draw-indirect.frag");
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

	GLsizei const VertexCount(12);
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec3);
	glm::vec3 const PositionData[VertexCount] =
	{
		glm::vec3(-1.0f,-1.0f, 0.5f),
		glm::vec3( 1.0f,-1.0f, 0.5f),
		glm::vec3( 1.0f, 1.0f, 0.5f),
		glm::vec3(-1.0f, 1.0f, 0.5f),

		glm::vec3(-0.5f,-1.0f, 0.0f),
		glm::vec3( 1.5f,-1.0f, 0.0f),
		glm::vec3( 0.5f, 1.0f, 0.0f),
		glm::vec3(-1.5f, 1.0f, 0.0f),

		glm::vec3(-0.5f,-1.0f,-0.5f),
		glm::vec3( 0.5f,-1.0f,-0.5f),
		glm::vec3( 1.5f, 1.0f,-0.5f),
		glm::vec3(-1.5f, 1.0f,-0.5f)
	};

	GLsizeiptr const ColorSize = VertexCount * sizeof(glm::vec3);
	glm::vec3 const ColorData[VertexCount] =
	{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	GLsizei const IndirectBufferCount(3);
	GLsizei const DrawCount[IndirectBufferCount] = {3, 2, 1};

	namespace buffer
	{
		enum type
		{
			POSITION,
			COLOR,
			ELEMENT,
			TRANSFORM,
			INDIRECT_A,
			INDIRECT_B,
			INDIRECT_C,
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
	bool Success(true);
	
	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);
	glBindProgramPipeline(0);

	GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE);
	GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE);

	ProgramName = glCreateProgram();
	glProgramParameteri(ProgramName, GL_PROGRAM_SEPARABLE, GL_TRUE);
	glAttachShader(ProgramName, VertShaderName);
	glAttachShader(ProgramName, FragShaderName);
	glDeleteShader(VertShaderName);
	glDeleteShader(FragShaderName);
	glLinkProgram(ProgramName);
	Success = glf::checkProgram(ProgramName);

	glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT, ProgramName);

	return Success;
}

bool initBuffer()
{
	glGenBuffers(buffer::MAX, BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::POSITION]);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::COLOR]);
    glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);	

	DrawElementsIndirectCommand CommandA[3];
	CommandA[0].count = ElementCount;
	CommandA[0].primCount = 1;
	CommandA[0].firstIndex = 0;
	CommandA[0].baseVertex = 0;
	CommandA[0].baseInstance = 0;
	CommandA[1].count = ElementCount;
	CommandA[1].primCount = 1;
	CommandA[1].firstIndex = 0;
	CommandA[1].baseVertex = 4;
	CommandA[1].baseInstance = 0;
	CommandA[2].count = ElementCount;
	CommandA[2].primCount = 1;
	CommandA[2].firstIndex = 0;
	CommandA[2].baseVertex = 8;
	CommandA[2].baseInstance = 0;

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, BufferName[buffer::INDIRECT_A]);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(CommandA), CommandA, GL_STATIC_DRAW);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

	DrawElementsIndirectCommand CommandB[2];
	CommandB[0].count = ElementCount;
	CommandB[0].primCount = 1;
	CommandB[0].firstIndex = 0;
	CommandB[0].baseVertex = 0;
	CommandB[0].baseInstance = 0;
	CommandB[1].count = ElementCount;
	CommandB[1].primCount = 1;
	CommandB[1].firstIndex = 0;
	CommandB[1].baseVertex = 4;
	CommandB[1].baseInstance = 0;

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, BufferName[buffer::INDIRECT_B]);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(CommandB), CommandB, GL_STATIC_DRAW);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

	DrawElementsIndirectCommand CommandC[1];
	CommandC[0].count = ElementCount;
	CommandC[0].primCount = 1;
	CommandC[0].firstIndex = 0;
	CommandC[0].baseVertex = 8;
	CommandC[0].baseInstance = 0;

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, BufferName[buffer::INDIRECT_C]);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(CommandC), CommandC, GL_STATIC_DRAW);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

	return true;
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::POSITION]);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribDivisor(glf::semantic::attr::POSITION, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::COLOR]);
		glVertexAttribPointer(glf::semantic::attr::COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribDivisor(glf::semantic::attr::COLOR, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]); 
	glBindVertexArray(0);

	return true;
}

bool initDebugOutput()
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return true;
}

bool begin()
{
	bool Success(true);

	// Validate OpenGL support
	Success = Success && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Success = Success && glf::checkExtension("GL_AMD_multi_draw_indirect");

	// Create and initialize objects
	if(Success && glf::checkExtension("GL_ARB_debug_output"))
		Success = initDebugOutput();
	if(Success)
		Success = initProgram();
	if(Success)
		Success = initBuffer();
	if(Success)
		Success = initVertexArray();

	// Set initial rendering states
	glEnable(GL_DEPTH_TEST);
	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size.x, Window.Size.y)[0]);
	glBindProgramPipeline(PipelineName);
	glBindVertexArray(VertexArrayName);
	glBindBufferBase(GL_UNIFORM_BUFFER, glf::semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);

	return Success && glf::checkError("begin");
}

bool end()
{
	// Delete objects
	glDeleteBuffers(buffer::MAX, BufferName);
	glDeleteProgramPipelines(1, &PipelineName);
	glDeleteProgram(ProgramName);
	glDeleteVertexArrays(1, &VertexArrayName);

	return true;
}

void display()
{
	// Selection of the indirect buffer to use
	if(Window.KeyPressed[32] >= IndirectBufferCount)
		Window.KeyPressed[32] = 0;

	std::size_t const IndirectBufferIndex = Window.KeyPressed[32];

	// Clear framebuffer
	float Depth(1.0f);
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f)[0]);

	// Update the transformation matrix
	glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
	glm::mat4* Pointer = (glm::mat4*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), 
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y + 45.0f, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x + 45.0f, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	*Pointer = MVP;
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	
	// Draw
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, BufferName[buffer::INDIRECT_A] + GLuint(IndirectBufferIndex));
	glMultiDrawElementsIndirectAMD(GL_TRIANGLES, GL_UNSIGNED_INT, 0, DrawCount[IndirectBufferIndex], sizeof(DrawElementsIndirectCommand));

	// Swap framebuffers
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
