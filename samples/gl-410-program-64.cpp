//**********************************
// OpenGL Double
// 02/08/2010 - 02/08/2010
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
	std::string const SAMPLE_NAME = "OpenGL Double";
	std::string const VERT_SHADER_SOURCE(glf::DATA_DIRECTORY + "gl-410/double.vert");
	std::string const FRAG_SHADER_SOURCE(glf::DATA_DIRECTORY + "gl-410/double.frag");
	int const SAMPLE_SIZE_WIDTH(640);
	int const SAMPLE_SIZE_HEIGHT(480);
	int const SAMPLE_MAJOR_VERSION(4);
	int const SAMPLE_MINOR_VERSION(1);

	glf::window Window(glm::ivec2(SAMPLE_SIZE_WIDTH, SAMPLE_SIZE_HEIGHT));

	GLsizei const VertexCount(4);
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::dvec3);
	glm::dvec3 const PositionData[VertexCount] =
	{
		glm::dvec3(-1.0f,-1.0f, 0.0f),
		glm::dvec3( 1.0f,-1.0f, 0.0f),
		glm::dvec3( 1.0f, 1.0f, 0.0f),
		glm::dvec3(-1.0f, 1.0f, 0.0f)
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(glm::uint16);
	glm::uint16 const ElementData[ElementCount] =
	{
		0, 1, 2,
		0, 2, 3
	};

	namespace buffer
	{
		enum type
		{
			F64,
			ELEMENT,
			MAX
		};
	}//namespace buffer

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
	GLuint BufferName[buffer::MAX] = {0, 0};
	GLuint VertexArrayName(0);
	GLint UniformMVP(0);
	GLint UniformDiffuse(0);

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

	if(Validated)
	{
		std::string VertexSourceContent = glf::loadFile(VERT_SHADER_SOURCE);
		char const * VertexSourcePointer = VertexSourceContent.c_str();
		ProgramName[program::VERT] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &VertexSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::VERT]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, ProgramName[program::VERT]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	if(Validated)
	{
		std::string FragmentSourceContent = glf::loadFile(FRAG_SHADER_SOURCE);
		char const * FragmentSourcePointer = FragmentSourceContent.c_str();
		ProgramName[program::FRAG] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &FragmentSourcePointer);
		Validated = Validated && glf::checkProgram(ProgramName[program::FRAG]);
	}

	if(Validated)
	{
		glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, ProgramName[program::FRAG]);
		Validated = Validated && glf::checkError("initProgram - stage");
	}

	// Get variables locations
	if(Validated)
	{
		UniformMVP = glGetUniformLocation(ProgramName[program::VERT], "MVP");
		UniformDiffuse = glGetUniformLocation(ProgramName[program::FRAG], "Diffuse");
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

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F64]);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);

    glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::F64]);
		glVertexAttribLPointer(glf::semantic::attr::POSITION, 3, GL_DOUBLE, sizeof(glm::dvec3), GLF_BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
	glBindVertexArray(0);

	return glf::checkError("initVertexArray");
}

bool validate(GLuint const & ProgramName)
{
	bool Error = false;

	// Pipeline object validation
	{
		GLint Status(0);
		GLint LengthMax(0);
		glValidateProgramPipeline(PipelineName);
		glGetProgramPipelineiv(PipelineName, GL_VALIDATE_STATUS, &Status);
		glGetProgramPipelineiv(PipelineName, GL_INFO_LOG_LENGTH, &LengthMax);

		GLsizei LengthQuery(0);
		std::vector<GLchar> InfoLog(LengthMax + 1, '\0');
		glGetProgramPipelineInfoLog(PipelineName, GLsizei(InfoLog.size()), &LengthQuery, &InfoLog[0]);

		glDebugMessageInsertARB(
			GL_DEBUG_SOURCE_APPLICATION_ARB, 
			GL_DEBUG_TYPE_OTHER_ARB, 76,
			GL_DEBUG_SEVERITY_LOW_ARB,
			LengthQuery, 
			&InfoLog[0]);
	}

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

		glf::vertexattrib VertexAttrib;
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &VertexAttrib.Enabled);
		//glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &VertexAttrib.Binding);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_SIZE, &VertexAttrib.Size);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &VertexAttrib.Stride);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_TYPE, &VertexAttrib.Type);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &VertexAttrib.Normalized);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_INTEGER, &VertexAttrib.Integer);
        glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &VertexAttrib.Divisor);
		glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_LONG, &VertexAttrib.Long);
		glGetVertexAttribPointerv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_POINTER, &VertexAttrib.Pointer);

		if(VertexAttrib.Integer == GL_TRUE)
		{
			if(!(
				VertexAttrib.Type == GL_INT ||  
				VertexAttrib.Type == GL_INT_VEC2 || 
				VertexAttrib.Type == GL_INT_VEC3 || 
				VertexAttrib.Type == GL_INT_VEC4 || 
				VertexAttrib.Type == GL_UNSIGNED_INT || 
				VertexAttrib.Type == GL_UNSIGNED_INT_VEC2 || 
				VertexAttrib.Type == GL_UNSIGNED_INT_VEC3 || 
				VertexAttrib.Type == GL_UNSIGNED_INT_VEC4))
				return true;

			if(!(
				VertexAttrib.Type == GL_BYTE || 
				VertexAttrib.Type == GL_UNSIGNED_BYTE || 
				VertexAttrib.Type == GL_SHORT || 
				VertexAttrib.Type == GL_UNSIGNED_SHORT || 
				VertexAttrib.Type == GL_INT || 
				VertexAttrib.Type == GL_UNSIGNED_INT))
				return true;

			//if(AttribSize > 1)
			//GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, and GL_DOUBLE
		}
		else if(VertexAttrib.Long == GL_TRUE) // OpenGL Spec bug 
        {
            if( VertexAttrib.Type == GL_DOUBLE || 
			    VertexAttrib.Type == GL_DOUBLE_VEC2 || 
			    VertexAttrib.Type == GL_DOUBLE_VEC3 || 
			    VertexAttrib.Type == GL_DOUBLE_VEC4 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT2 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT3 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT4 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT2x3 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT2x4 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT3x2 ||
			    VertexAttrib.Type == GL_DOUBLE_MAT3x4 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT4x2 || 
			    VertexAttrib.Type == GL_DOUBLE_MAT4x3)
		    {
			    if(VertexAttrib.Type != GL_DOUBLE)
				    return true;
		    }
		    else// if((VertexAttrib.Normalized == GL_TRUE) || (GL_VERTEX_ATTRIB_ARRAY_FLOAT == GL_TRUE))
		    {
			    if(!(
				    VertexAttrib.Type == GL_FLOAT ||  
				    VertexAttrib.Type == GL_FLOAT_VEC2 || 
				    VertexAttrib.Type == GL_FLOAT_VEC3 || 
				    VertexAttrib.Type == GL_FLOAT_VEC4 || 
				    VertexAttrib.Type == GL_FLOAT_MAT2 || 
				    VertexAttrib.Type == GL_FLOAT_MAT3 || 
				    VertexAttrib.Type == GL_FLOAT_MAT4 || 
				    VertexAttrib.Type == GL_FLOAT_MAT2x3 || 
				    VertexAttrib.Type == GL_FLOAT_MAT2x4 || 
				    VertexAttrib.Type == GL_FLOAT_MAT3x2 || 
				    VertexAttrib.Type == GL_FLOAT_MAT3x4 || 
				    VertexAttrib.Type == GL_FLOAT_MAT4x2 || 
				    VertexAttrib.Type == GL_FLOAT_MAT4x3))
				    return true;

			    // It could be any vertex array attribute type
		    }
        }

		printf("glGetActiveAttrib(\n\t%d, \n\t%d, \n\t%d, \n\t%d, \n\t%d, \n\t%s)\n", 
			i, AttribLocation, AttribLength, AttribSize, AttribType, NameString.c_str());
	}

	return Error;
}

bool begin()
{
	bool Validated = glf::checkGLVersion(SAMPLE_MAJOR_VERSION, SAMPLE_MINOR_VERSION);

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
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
	glDeleteVertexArrays(1, &VertexArrayName);
	glDeleteProgram(ProgramName[program::VERT]);
	glDeleteProgram(ProgramName[program::FRAG]);
	glBindProgramPipeline(0);
	glDeleteProgramPipelines(1, &PipelineName);

	return glf::checkError("end");
}

void display()
{
    glm::dmat4 Projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
	glm::dmat4 ViewTranslateZ = glm::translate(glm::dmat4(1.0), glm::dvec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	glm::dmat4 ViewRotateX = glm::rotate(ViewTranslateZ, double(Window.RotationCurrent.y), glm::dvec3(1.f, 0.f, 0.f));
	glm::dmat4 ViewRotateY = glm::rotate(ViewRotateX, double(Window.RotationCurrent.x), glm::dvec3(0.f, 1.f, 0.f));
	glm::dmat4 View = ViewRotateY;
	glm::dmat4 Model = glm::dmat4(1.0f);
	glm::dmat4 MVP = Projection * View * Model;

	glProgramUniformMatrix4dv(ProgramName[program::VERT], UniformMVP, 1, GL_FALSE, &MVP[0][0]);
	glProgramUniform4dv(ProgramName[program::FRAG], UniformDiffuse, 1, &glm::dvec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

	glViewportIndexedfv(0, &glm::vec4(0, 0, Window.Size.x, Window.Size.y)[0]);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f)[0]);

	glBindProgramPipeline(PipelineName);

	validate(ProgramName[program::VERT]);

	glBindVertexArray(VertexArrayName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1, 0);

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
