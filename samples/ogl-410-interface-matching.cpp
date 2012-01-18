//**********************************
// OpenGL Shader Interface Matching
// 25/07/2011 - 25/07/2011
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
	std::string const SAMPLE_NAME = "OpenGL Shader Interface Matching";	
	std::string const SAMPLE_VERT_SHADER(glf::DATA_DIRECTORY + "410/interface-matching.vert");
	std::string const SAMPLE_CONT_SHADER(glf::DATA_DIRECTORY + "410/interface-matching.cont");
	std::string const SAMPLE_EVAL_SHADER(glf::DATA_DIRECTORY + "410/interface-matching.eval");
	std::string const SAMPLE_GEOM_SHADER(glf::DATA_DIRECTORY + "410/interface-matching.geom");
	std::string const SAMPLE_FRAG_SHADER(glf::DATA_DIRECTORY + "410/interface-matching.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fc4f);
	glf::vertex_v2fc4f const VertexData[VertexCount] =
	{
		glf::vertex_v2fc4f(glm::vec2(-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2( 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
		glf::vertex_v2fc4f(glm::vec2(-1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
	};

	namespace program
	{
		enum type
		{
			VERT,
			FRAG,
			MAX
		};
	}//namespace program

	GLuint PipelineName(0);
	GLuint ProgramName[program::MAX] = {0, 0};
	GLuint ArrayBufferName(0);
	GLuint VertexArrayName(0);
	GLint UniformMVP(0);
}//namespace

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool initProgram()
{
	bool Validated = true;
	
	glGenProgramPipelines(1, &PipelineName);
	glBindProgramPipeline(PipelineName);
	glBindProgramPipeline(0);

	if(Validated)
	{
		GLuint VertShaderName = glf::createShader(GL_VERTEX_SHADER, SAMPLE_VERT_SHADER);
		GLuint ContShaderName = glf::createShader(GL_TESS_CONTROL_SHADER, SAMPLE_CONT_SHADER);
		GLuint EvalShaderName = glf::createShader(GL_TESS_EVALUATION_SHADER, SAMPLE_EVAL_SHADER);
		GLuint GeomShaderName = glf::createShader(GL_GEOMETRY_SHADER, SAMPLE_GEOM_SHADER);
		GLuint FragShaderName = glf::createShader(GL_FRAGMENT_SHADER, SAMPLE_FRAG_SHADER);

		ProgramName[program::VERT] = glCreateProgram();
		ProgramName[program::FRAG] = glCreateProgram();
		glProgramParameteri(ProgramName[program::VERT], GL_PROGRAM_SEPARABLE, GL_TRUE);
		glProgramParameteri(ProgramName[program::FRAG], GL_PROGRAM_SEPARABLE, GL_TRUE);

		glAttachShader(ProgramName[program::VERT], VertShaderName);
		glAttachShader(ProgramName[program::VERT], ContShaderName);
		glAttachShader(ProgramName[program::VERT], EvalShaderName);
		glAttachShader(ProgramName[program::VERT], GeomShaderName);
		glLinkProgram(ProgramName[program::VERT]);

		glAttachShader(ProgramName[program::FRAG], FragShaderName);
		glLinkProgram(ProgramName[program::FRAG]);

		glDeleteShader(VertShaderName);
		glDeleteShader(ContShaderName);
		glDeleteShader(EvalShaderName);
		glDeleteShader(GeomShaderName);
		glDeleteShader(FragShaderName);

		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT | GL_TESS_CONTROL_SHADER_BIT | GL_TESS_EVALUATION_SHADER_BIT | GL_GEOMETRY_SHADER_BIT, ProgramName[program::VERT]);
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName[program::VERT], "MVP");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fc4f), GLF_BUFFER_OFFSET(sizeof(glm::vec2)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::COLOR);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool initArrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(1, &ArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool begin()
{
	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
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
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteBuffers(1, &ArrayBufferName);
	for(std::size_t i = 0; i < program::MAX; ++i)
		glDeleteProgram(ProgramName[i]);

	return glf::checkError("end");
}

bool validate(GLuint const & ProgramName)
{
	bool Error = false;

	GLint ActiveAttributeMaxLength(0);
	GLint ActiveAttribute(0);
	glGetProgramiv(ProgramName, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &ActiveAttributeMaxLength);
	glGetProgramiv(ProgramName, GL_ACTIVE_ATTRIBUTES, &ActiveAttribute);

	GLsizei AttribLength(0);
	GLint AttribSize(0);
	GLenum AttribType(0);
	std::vector<GLchar> AttribName(ActiveAttributeMaxLength, '\0');

	for(GLint i = 0; i < ActiveAttribute; ++i)
	{
		glGetActiveAttrib(ProgramName,
 			GLuint(i),
 			GLsizei(ActiveAttributeMaxLength),
 			&AttribLength,
 			&AttribSize,
 			&AttribType,
 			&AttribName[0]);

		std::string NameString;
		NameString.insert(NameString.begin(), AttribName.begin(), AttribName.end());
		std::vector<GLchar> NameSwap(ActiveAttributeMaxLength, '\0');
		std::swap(AttribName, NameSwap);

		GLint AttribLocation = glGetAttribLocation(ProgramName, NameString.c_str());

		GLint VertexAttribEnabled(0);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &VertexAttribEnabled);
		if(VertexAttribEnabled == GL_FALSE)
			return true;

		GLint VertexAttribSize(0);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_SIZE, &VertexAttribSize);
		//GLint VertexAttribStride(0);
		//glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &VertexAttribStride);
		GLint VertexAttribType(0);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_TYPE, &VertexAttribType);
		GLint VertexAttribNormalized(0);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &VertexAttribNormalized);
		GLint VertexAttribInteger(0);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_INTEGER, &VertexAttribInteger);
		//GLint VertexAttribLong(0);
		//glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_LONG, &VertexAttribLong);

		if(GL_VERTEX_ATTRIB_ARRAY_INTEGER == GL_TRUE)
		{
			if(!(
				AttribType == GL_INT ||  
				AttribType == GL_INT_VEC2 || 
				AttribType == GL_INT_VEC3 || 
				AttribType == GL_INT_VEC4 || 
				AttribType == GL_UNSIGNED_INT || 
				AttribType == GL_UNSIGNED_INT_VEC2 || 
				AttribType == GL_UNSIGNED_INT_VEC3 || 
				AttribType == GL_UNSIGNED_INT_VEC4))
				return true;

			if(!(
				VertexAttribType == GL_BYTE || 
				VertexAttribType == GL_UNSIGNED_BYTE || 
				VertexAttribType == GL_SHORT || 
				VertexAttribType == GL_UNSIGNED_SHORT || 
				VertexAttribType == GL_INT || 
				VertexAttribType == GL_UNSIGNED_INT))
				return true;

			//if(AttribSize > 1)
			//GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, and GL_DOUBLE
		}
		//else if(GL_VERTEX_ATTRIB_ARRAY_LONG == GL_TRUE) // OpenGL Spec bug 
		else if(
			AttribType == GL_DOUBLE || 
			AttribType == GL_DOUBLE_VEC2 || 
			AttribType == GL_DOUBLE_VEC3 || 
			AttribType == GL_DOUBLE_VEC4 || 
			AttribType == GL_DOUBLE_MAT2 || 
			AttribType == GL_DOUBLE_MAT3 || 
			AttribType == GL_DOUBLE_MAT4 || 
			AttribType == GL_DOUBLE_MAT2x3 || 
			AttribType == GL_DOUBLE_MAT2x4 || 
			AttribType == GL_DOUBLE_MAT3x2 ||
			AttribType == GL_DOUBLE_MAT3x4 || 
			AttribType == GL_DOUBLE_MAT4x2 || 
			AttribType == GL_DOUBLE_MAT4x3)
		{
			if(VertexAttribType != GL_DOUBLE)
				return true;
		}
		else //if((GL_VERTEX_ATTRIB_ARRAY_NORMALIZED == GL_TRUE) || (GL_VERTEX_ATTRIB_ARRAY_FLOAT == GL_TRUE))
		{
			if(!(
				AttribType == GL_FLOAT ||  
				AttribType == GL_FLOAT_VEC2 || 
				AttribType == GL_FLOAT_VEC3 || 
				AttribType == GL_FLOAT_VEC4 || 
				AttribType == GL_FLOAT_MAT2 || 
				AttribType == GL_FLOAT_MAT3 || 
				AttribType == GL_FLOAT_MAT4 || 
				AttribType == GL_FLOAT_MAT2x3 || 
				AttribType == GL_FLOAT_MAT2x4 || 
				AttribType == GL_FLOAT_MAT3x2 || 
				AttribType == GL_FLOAT_MAT3x4 || 
				AttribType == GL_FLOAT_MAT4x2 || 
				AttribType == GL_FLOAT_MAT4x3))
				return true;

			// It could be any vertex array attribute type
		}

		printf("glGetActiveAttrib(\n\t%d, \n\t%d, \n\t%d, \n\t%d, \n\t%d, \n\t%s)\n", 
			i, AttribLocation, AttribLength, AttribSize, AttribType, NameString.c_str());
	}

	return Error;
}

void display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	glProgramUniformMatrix4fv(ProgramName[program::VERT], UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size)[0]);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glBindProgramPipeline(PipelineName);

	glBindVertexArray(VertexArrayName);
	glPatchParameteri(GL_PATCH_VERTICES, VertexCount);

	assert(!validate(ProgramName[program::VERT]));
	glDrawArraysInstanced(GL_PATCHES, 0, VertexCount, 1);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	return glf::run(
		argc, argv,
		glm::ivec2(::SAMPLE_SIZE_WIDTH, ::SAMPLE_SIZE_HEIGHT), 
		::SAMPLE_MAJOR_VERSION, 
		::SAMPLE_MINOR_VERSION);
}
