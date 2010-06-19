//**********************************
// OpenGL Transform Feedback
// 06/04/2010
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
	std::string const SAMPLE_NAME = "OpenGL Transform Feedback";
	std::string const VERTEX_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "330/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "330/flat-color.frag");
	std::string const VERTEX_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "330/transformed.vert");
	std::string const FRAGMENT_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "330/flat-color.frag");
	int const SAMPLE_SIZE_WIDTH = 640;
	int const SAMPLE_SIZE_HEIGHT = 480;
	int const SAMPLE_MAJOR_VERSION = 3;
	int const SAMPLE_MINOR_VERSION = 3;

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount = 6;
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};

	GLuint TransformProgramName = 0;
	GLuint TransformArrayBufferName = 0;
	GLuint TransformVertexArrayName = 0;
	GLint TransformUniformDiffuse = 0;
	GLint TransformUniformMVP = 0;

	GLuint FeedbackProgramName = 0;
	GLuint FeedbackArrayBufferName = 0;
	GLuint FeedbackVertexArrayName = 0;
	GLint FeedbackUniformDiffuse = 0;
	GLint FeedbackUniformMVP = 0;

	GLuint Query = 0;

}//namespace

bool initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		TransformProgramName = glf::createProgram(VERTEX_SHADER_SOURCE_TRANSFORM, FRAGMENT_SHADER_SOURCE_TRANSFORM);
		GLchar const * Strings[] = {"gl_Position"}; 
		glTransformFeedbackVaryings(TransformProgramName, 1, Strings, GL_SEPARATE_ATTRIBS); 
		glLinkProgram(TransformProgramName);
		Validated = Validated && glf::checkProgram(TransformProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		TransformUniformMVP = glGetUniformLocation(TransformProgramName, "MVP");
		TransformUniformDiffuse = glGetUniformLocation(TransformProgramName, "Diffuse");
	}

	// Create program
	if(Validated)
	{
		FeedbackProgramName = glf::createProgram(VERTEX_SHADER_SOURCE_FEEDBACK, FRAGMENT_SHADER_SOURCE_FEEDBACK);
		glLinkProgram(FeedbackProgramName);
		Validated = Validated && glf::checkProgram(FeedbackProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		FeedbackUniformDiffuse = glGetUniformLocation(FeedbackProgramName, "Diffuse");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	// Build a vertex array object
	glGenVertexArrays(1, &TransformVertexArrayName);
    glBindVertexArray(TransformVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, TransformArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Build a vertex array object
	glGenVertexArrays(1, &FeedbackVertexArrayName);
    glBindVertexArray(FeedbackVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, FeedbackArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &TransformArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, TransformArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &FeedbackArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, FeedbackArrayBufferName);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * VertexCount, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool begin()
{
	glGenQueries(1, &Query);

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
	glDeleteVertexArrays(1, &TransformVertexArrayName);
	glDeleteBuffers(1, &TransformArrayBufferName);
	glDeleteProgram(TransformProgramName);

	glDeleteVertexArrays(1, &FeedbackVertexArrayName);
	glDeleteBuffers(1, &FeedbackArrayBufferName);
	glDeleteProgram(FeedbackProgramName);

	glDeleteQueries(1, &Query);

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

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// First draw, capture the attributes
	{
		// Disable rasterisation, vertices processing only!
		glEnable(GL_RASTERIZER_DISCARD);

		glUseProgram(TransformProgramName);
		glUniformMatrix4fv(TransformUniformMVP, 1, GL_FALSE, &MVP[0][0]);
		glUniform4fv(TransformUniformDiffuse, 1, &glm::vec4(0.0f, 0.5f, 1.0f, 1.0f)[0]);

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, FeedbackArrayBufferName); 

		glBindVertexArray(TransformVertexArrayName);

		glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, Query); 
		glBeginTransformFeedback(GL_TRIANGLES);
			glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glEndTransformFeedback();
		glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN); 

		glDisable(GL_RASTERIZER_DISCARD);
	}

	// Second draw, reuse the captured attributes
	{
		glUseProgram(FeedbackProgramName);
		glUniform4fv(FeedbackUniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		GLuint PrimitivesWritten = 0;
		glGetQueryObjectuiv(Query, GL_QUERY_RESULT, &PrimitivesWritten);

		glBindVertexArray(FeedbackVertexArrayName);
		glDrawArrays(GL_TRIANGLES, 0, PrimitivesWritten * 3);
	}

	glf::swapBuffers();
	glf::checkError("display");
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
