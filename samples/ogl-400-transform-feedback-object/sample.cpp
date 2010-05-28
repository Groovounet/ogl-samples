//**********************************
// OpenGL Transform Feedback Object
// 20/05/2010
//**********************************
// Christophe Riccio
// g.truc.creation@gmail.com
//**********************************
// G-Truc Creation
// www.g-truc.net
//**********************************

#include "sample.hpp"

namespace
{
	std::string const SAMPLE_NAME = "OpenGL Transform Feedback Object";
	GLint const SAMPLE_MAJOR_VERSION = 3;
	GLint const SAMPLE_MINOR_VERSION = 3;
	std::string const VERTEX_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "400/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "400/flat-color.frag");
	std::string const VERTEX_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "400/transformed.vert");
	std::string const FRAGMENT_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "400/transformed.frag");

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

}//namespace

sample::sample
(
	std::string const & Name, 
	glm::ivec2 const & WindowSize,
	glm::uint32 const & VersionMajor,
	glm::uint32 const & VersionMinor
) :
	window(Name, WindowSize, VersionMajor, VersionMinor),
	TransformProgramName(0),
	FeedbackProgramName(0)
{}

sample::~sample()
{}

bool sample::check() const
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Version = (MajorVersion * 10 + MinorVersion) >= (SAMPLE_MAJOR_VERSION * 10 + SAMPLE_MINOR_VERSION);
	return Version && glf::checkError("sample::check");
}

bool sample::begin(glm::ivec2 const & WindowSize)
{
	this->WindowSize = WindowSize;

	glGenQueries(1, &this->Query);

	bool Validated = true;
	if(Validated)
		Validated = this->initProgram();
	if(Validated)
		Validated = this->initArrayBuffer();
	if(Validated)
		Validated = this->initVertexArray();
	if(Validated)
		Validated = this->initFeedback();

	return Validated && glf::checkError("sample::begin");
}

bool sample::end()
{
	glDeleteVertexArrays(1, &this->TransformVertexArrayName);
	glDeleteBuffers(1, &this->TransformArrayBufferName);
	glDeleteProgram(this->TransformProgramName);

	glDeleteVertexArrays(1, &this->FeedbackVertexArrayName);
	glDeleteBuffers(1, &this->FeedbackArrayBufferName);
	glDeleteProgram(this->FeedbackProgramName);

	glDeleteQueries(1, &this->Query);

	return glf::checkError("sample::end");
}

void sample::render()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, RotationCurrent.y, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, this->WindowSize.x, this->WindowSize.y);

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// First draw, capture the attributes
	{
		// Disable rasterisation, vertices processing only!
		glEnable(GL_RASTERIZER_DISCARD);

		glUseProgram(this->TransformProgramName);
		glUniformMatrix4fv(this->TransformUniformMVP, 1, GL_FALSE, &MVP[0][0]);
		glUniform4fv(this->TransformUniformDiffuse, 1, &glm::vec4(1.00f, 0.50f, 0.00f, 1.0f)[0]);

		glBindVertexArray(this->TransformVertexArrayName);

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->FeedbackName);
		glBeginTransformFeedback(GL_TRIANGLES);
			glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glEndTransformFeedback();
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

		glDisable(GL_RASTERIZER_DISCARD);
	}

	// Second draw, reuse the captured attributes
	{
		glUseProgram(this->FeedbackProgramName);
		glUniformMatrix4fv(this->TransformUniformMVP, 1, GL_FALSE, &MVP[0][0]);
		glUniform4fv(this->FeedbackUniformDiffuse, 1, &glm::vec4(0.00f, 0.50f, 1.00f, 1.00f)[0]);

		glBindVertexArray(this->FeedbackVertexArrayName);
		glDrawTransformFeedback(GL_TRIANGLES, this->FeedbackName);
	}

	glf::checkError("sample::render");
}

bool sample::initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		this->TransformProgramName = glf::createProgram(VERTEX_SHADER_SOURCE_TRANSFORM, FRAGMENT_SHADER_SOURCE_TRANSFORM);
		GLchar const * Strings[] = {"gl_Position"}; 
		glTransformFeedbackVaryings(this->TransformProgramName, 1, Strings, GL_SEPARATE_ATTRIBS); 
		glLinkProgram(this->TransformProgramName);
		Validated = Validated && glf::checkProgram(this->TransformProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		this->TransformUniformMVP = glGetUniformLocation(this->TransformProgramName, "MVP");
		this->TransformUniformDiffuse = glGetUniformLocation(this->TransformProgramName, "Diffuse");
	}

	// Create program
	if(Validated)
	{
		this->FeedbackProgramName = glf::createProgram(VERTEX_SHADER_SOURCE_FEEDBACK, FRAGMENT_SHADER_SOURCE_FEEDBACK);
		glLinkProgram(this->FeedbackProgramName);
		Validated = Validated && glf::checkProgram(this->FeedbackProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		this->FeedbackUniformDiffuse = glGetUniformLocation(this->FeedbackProgramName, "Diffuse");
	}

	return Validated && glf::checkError("sample::initProgram");
}

bool sample::initVertexArray()
{
	// Build a vertex array object
	glGenVertexArrays(1, &this->TransformVertexArrayName);
    glBindVertexArray(this->TransformVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, this->TransformArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Build a vertex array object
	glGenVertexArrays(1, &this->FeedbackVertexArrayName);
    glBindVertexArray(this->FeedbackVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, this->FeedbackArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return glf::checkError("sample::initVertexArray");
}

bool sample::initFeedback()
{
	// Generate a buffer object
	glGenTransformFeedbacks(1, &this->FeedbackName);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->FeedbackName);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->FeedbackArrayBufferName); 
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	return glf::checkError("sample::initFeedback");
}

bool sample::initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &this->TransformArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, this->TransformArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &this->FeedbackArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, this->FeedbackArrayBufferName);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * VertexCount, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("sample::initArrayBuffer");
}

int main(int argc, char* argv[])
{
	glm::ivec2 ScreenSize(640, 480);

	sample* Sample = new sample(
		SAMPLE_NAME, 
		ScreenSize, 
		SAMPLE_MAJOR_VERSION,
		SAMPLE_MINOR_VERSION);

	if(Sample->check())
	{
		Sample->begin(ScreenSize);
		Sample->run();
		Sample->end();

		delete Sample;
		return 0;
	}

	fprintf(stderr, "OpenGL Error: this sample failed to run\n");

	delete Sample;
	Sample = 0;
	return 1;
}


/*
#include "sample.hpp"

namespace
{
	std::string const SAMPLE_NAME = "OpenGL transform feedback object";
	GLint const SAMPLE_MAJOR_VERSION = 3;
	GLint const SAMPLE_MINOR_VERSION = 3;
	std::string const VERTEX_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "400/flat-color.vert");
	std::string const FRAGMENT_SHADER_SOURCE_TRANSFORM(glf::DATA_DIRECTORY + "400/flat-color.frag");
	std::string const VERTEX_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "400/transformed.vert");
	std::string const FRAGMENT_SHADER_SOURCE_FEEDBACK(glf::DATA_DIRECTORY + "400/flat-color.frag");

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

}//namespace

sample::sample
(
	std::string const & Name, 
	glm::ivec2 const & WindowSize,
	glm::uint32 const & VersionMajor,
	glm::uint32 const & VersionMinor
) :
	window(Name, WindowSize, VersionMajor, VersionMinor),
	TransformProgramName(0),
	FeedbackProgramName(0)
{}

sample::~sample()
{}

bool sample::check() const
{
	GLint MajorVersion = 0;
	GLint MinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
	bool Version = (MajorVersion * 10 + MinorVersion) >= (glf::SAMPLE_MAJOR * 10 + glf::SAMPLE_MINOR);
	return Version && glf::checkError("sample::check");
}

bool sample::begin(glm::ivec2 const & WindowSize)
{
	this->WindowSize = WindowSize;

	glGenQueries(1, &this->Query);

	bool Validated = true;
	if(Validated)
		Validated = this->initProgram();
	if(Validated)
		Validated = this->initArrayBuffer();
	if(Validated)
		Validated = this->initVertexArray();
	//if(Validated)
	//	Validated = this->initFeedback();

	return Validated && glf::checkError("sample::begin");
}

bool sample::end()
{
	glDeleteVertexArrays(1, &this->TransformVertexArrayName);
	glDeleteBuffers(1, &this->TransformArrayBufferName);
	glDeleteProgram(this->TransformProgramName);

	glDeleteVertexArrays(1, &this->FeedbackVertexArrayName);
	glDeleteBuffers(1, &this->FeedbackArrayBufferName);
	glDeleteProgram(this->FeedbackProgramName);

	glDeleteQueries(1, &this->Query);

	return glf::checkError("sample::end");
}

void sample::render()
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, RotationCurrent.y, glm::vec3(-1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, this->WindowSize.x, this->WindowSize.y);

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// First draw, capture the attributes
	{
		// Disable rasterisation, vertices processing only!
		glEnable(GL_RASTERIZER_DISCARD);

		glUseProgram(this->TransformProgramName);
		glUniformMatrix4fv(this->TransformUniformMVP, 1, GL_FALSE, &MVP[0][0]);
		glUniform4fv(this->TransformUniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		//glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->FeedbackName);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->FeedbackArrayBufferName); 

		glBindVertexArray(this->TransformVertexArrayName);

		glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, this->Query); 
		glBeginTransformFeedback(GL_TRIANGLES);
			glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glEndTransformFeedback();
		glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN); 
	}

	// Second draw, reuse the captured attributes
	{
		glUseProgram(this->FeedbackProgramName);
		glUniform4fv(this->FeedbackUniformDiffuse, 1, &glm::vec4(0.0f, 0.5f, 1.0f, 1.0f)[0]);

		GLuint PrimitivesWritten = 0;
		glGetQueryObjectuiv(this->Query, GL_QUERY_RESULT, &PrimitivesWritten);

		glBindVertexArray(this->FeedbackVertexArrayName);
		glDrawArrays(GL_TRIANGLES, 0, PrimitivesWritten * 3);
		//glDrawTransformFeedback(GL_TRIANGLES, this->FeedbackName);
	}

	glf::checkError("sample::render");
}

bool sample::initProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		this->TransformProgramName = glf::createProgram(VERTEX_SHADER_SOURCE_TRANSFORM, FRAGMENT_SHADER_SOURCE_TRANSFORM);
		GLchar const * Strings[] = {"gl_Position"}; 
		glTransformFeedbackVaryings(this->TransformProgramName, 1, Strings, GL_SEPARATE_ATTRIBS); 
		glLinkProgram(this->TransformProgramName);
		Validated = Validated && glf::checkProgram(this->TransformProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		this->TransformUniformMVP = glGetUniformLocation(this->TransformProgramName, "MVP");
		this->TransformUniformDiffuse = glGetUniformLocation(this->TransformProgramName, "Diffuse");
	}

	// Create program
	if(Validated)
	{
		this->FeedbackProgramName = glf::createProgram(VERTEX_SHADER_SOURCE_FEEDBACK, FRAGMENT_SHADER_SOURCE_FEEDBACK);
		glLinkProgram(this->FeedbackProgramName);
		Validated = Validated && glf::checkProgram(this->FeedbackProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		this->FeedbackUniformDiffuse = glGetUniformLocation(this->FeedbackProgramName, "Diffuse");
	}

	return Validated && glf::checkError("sample::initProgram");
}

bool sample::initVertexArray()
{
	// Build a vertex array object
	glGenVertexArrays(1, &this->TransformVertexArrayName);
    glBindVertexArray(this->TransformVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, this->TransformArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Build a vertex array object
	glGenVertexArrays(1, &this->FeedbackVertexArrayName);
    glBindVertexArray(this->FeedbackVertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, this->FeedbackArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return glf::checkError("sample::initVertexArray");
}

bool sample::initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &this->TransformArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, this->TransformArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &this->FeedbackArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, this->FeedbackArrayBufferName);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * VertexCount, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("sample::initArrayBuffer");
}

bool sample::initFeedback()
{
	// Generate a buffer object
	glGenTransformFeedbacks(1, &this->FeedbackName);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->FeedbackName);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->FeedbackArrayBufferName); 
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	return glf::checkError("sample::initFeedback");
}

int main(int argc, char* argv[])
{
	glm::ivec2 ScreenSize(640, 480);

	sample* Sample = new sample(
		SAMPLE_NAME, 
		ScreenSize, 
		SAMPLE_MAJOR_VERSION,
		SAMPLE_MINOR_VERSION);

	if(Sample->check())
	{
		Sample->begin(ScreenSize);
		Sample->run();
		Sample->end();

		delete Sample;
		return 0;
	}

	fprintf(stderr, "OpenGL Error: this sample failed to run\n");

	delete Sample;
	Sample = 0;
	return 1;
}
*/