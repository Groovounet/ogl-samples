//**********************************
// OpenGL Samples Pack 
// ogl-samples.g-truc.net
//**********************************
// OpenGL Transform Feedback Instanced
// 01/07/2011 - 02/07/2011
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
	std::string const SAMPLE_NAME = "OpenGL Transform Feedback Instanced";
	std::string const VERT_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "420/transform-stream.vert");
	std::string const GEOM_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "420/transform-stream.geom");
	std::string const VERT_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "420/feedback-stream.vert");
	std::string const FRAG_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "420/feedback-stream.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(2);

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glm::vec4);
	glm::vec4 const VertexData[VertexCount] =
	{
		glm::vec4(-1.0f,-1.0f, 0.0f, 1.0f),
		glm::vec4( 1.0f,-1.0f, 0.0f, 1.0f),
		glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f)
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLuint);
	GLuint const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLuint FeedbackName(0);

	GLuint TransformProgramName(0);
	GLuint TransformArrayBufferName(0);
	GLuint TransformElementBufferName(0);
	GLuint TransformVertexArrayName(0);
	GLint TransformUniformMVP(0);

	GLuint FeedbackProgramName(0);
	GLuint FeedbackArrayBufferName(0);
	GLuint FeedbackVertexArrayName(0);
	GLint FeedbackUniformMVP(0);

	GLuint Query(0);

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE_TRANSFORM);
		GLuint GeomShaderName = glf::createShader(GL_GEOMETRY_SHADER, GEOM_SHADER_SOURCE_TRANSFORM);

		TransformProgramName = glCreateProgram();
		glAttachShader(TransformProgramName, VertShaderName);
		glAttachShader(TransformProgramName, GeomShaderName);
		glDeleteShader(VertShaderName);
		glDeleteShader(GeomShaderName);

		GLchar const * Strings[] = {"gl_Position", "block.Color"}; 
		glTransformFeedbackVaryings(TransformProgramName, 2, Strings, GL_INTERLEAVED_ATTRIBS);
		glLinkProgram(TransformProgramName);

		Validated = Validated && glf::checkProgram(TransformProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		TransformUniformMVP = glGetUniformLocation(TransformProgramName, "MVP");
		Validated = Validated && (TransformUniformMVP >= 0);
	}

	// Create program
	if(Validated)
	{
		GLuint VertexShaderName = glf::createShader(GL_VERTEX_SHADER, VERT_SHADER_SOURCE_FEEDBACK);
		GLuint FragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, FRAG_SHADER_SOURCE_FEEDBACK);

		FeedbackProgramName = glCreateProgram();
		glAttachShader(FeedbackProgramName, VertexShaderName);
		glAttachShader(FeedbackProgramName, FragmentShaderName);
		glDeleteShader(VertexShaderName);
		glDeleteShader(FragmentShaderName);
		glLinkProgram(FeedbackProgramName);
		Validated = Validated && glf::checkProgram(FeedbackProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		FeedbackUniformMVP = glGetUniformLocation(FeedbackProgramName, "MVP");
		Validated = Validated && (FeedbackUniformMVP >= 0);
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	glf::checkError("initVertexArray 0");

	// Build a vertex array object
	glGenVertexArrays(1, &TransformVertexArrayName);
    glBindVertexArray(TransformVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, TransformArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	glf::checkError("initVertexArray 1");

	// Build a vertex array object
	glGenVertexArrays(1, &FeedbackVertexArrayName);
    glBindVertexArray(FeedbackVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, FeedbackArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fc4f), 0);
		glVertexAttribPointer(glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fc4f), GLF_BUFFER_OFFSET(sizeof(glm::vec4)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initFeedback()
{
	// Generate a buffer object
	glGenTransformFeedbacks(1, &FeedbackName);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, FeedbackArrayBufferName); 
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	return glf::checkError("initFeedback");
}

bool initArrayBuffer()
{
	glGenBuffers(1, &TransformElementBufferName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TransformElementBufferName);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &TransformArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, TransformArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &FeedbackArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, FeedbackArrayBufferName);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glf::vertex_v4fc4f) * 6, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initDebugOutput()
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return glf::checkError("initDebugOutput");
}

bool initTest()
{
	bool Validated = true;
	glEnable(GL_DEPTH_TEST);

	return Validated && glf::checkError("initTest");
}

bool begin()
{
	bool Validated = true;
	Validated = Validated && glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);
	Validated = Validated && glf::checkExtension("GL_ARB_transform_feedback_instanced");

	glGenQueries(1, &Query);

	//if(Validated)
	//	Validated = initDebugOutput();
	if(Validated)
		Validated = initTest();
	if(Validated)
		Validated = initProgram();
	if(Validated)
		Validated = initArrayBuffer();
	if(Validated)
		Validated = initVertexArray();
	if(Validated)
		Validated = initFeedback();

	return Validated && glf::checkError("begin");
}

bool end()
{
	glf::checkError("end 0");

	glDeleteVertexArrays(1, &TransformVertexArrayName);
	glDeleteBuffers(1, &TransformArrayBufferName);
	glDeleteProgram(TransformProgramName);

	glDeleteVertexArrays(1, &FeedbackVertexArrayName);
	glDeleteBuffers(1, &FeedbackArrayBufferName);
	glDeleteProgram(FeedbackProgramName);

	glDeleteQueries(1, &Query);
	glDeleteTransformFeedbacks(1, &FeedbackName);

	return glf::checkError("end");
}

void display()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	float Depth(1.0f);
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

	// First draw, capture the attributes
	// Disable rasterisation, vertices processing only!
	glEnable(GL_RASTERIZER_DISCARD);

	glUseProgram(TransformProgramName);
	glUniformMatrix4fv(TransformUniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glBindVertexArray(TransformVertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TransformElementBufferName);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName);
	glBeginTransformFeedback(GL_TRIANGLES);
		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_INT, NULL, 1, 0);
	glEndTransformFeedback();
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	glDisable(GL_RASTERIZER_DISCARD);

	// Second draw, reuse the captured attributes
	glUseProgram(FeedbackProgramName);
	glUniformMatrix4fv(FeedbackUniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glBindVertexArray(FeedbackVertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDrawTransformFeedbackInstanced(GL_TRIANGLE_STRIP, FeedbackName, 5);

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
