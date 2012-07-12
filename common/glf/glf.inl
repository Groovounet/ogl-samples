#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

bool check();
bool begin();
bool end();
void display();

#if (defined(WIN32))

// GL_ARB_clear_buffer_object
typedef void (GLAPIENTRY * PFNGLCLEARBUFFERDATAPROC) (
	GLenum target, GLenum internalformat, GLenum format, GLenum type, const GLvoid * data);
typedef void (GLAPIENTRY * PFNGLCLEARBUFFERSUBDATAPROC) (
	GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const GLvoid * data);
typedef void (GLAPIENTRY * PFNGLCLEARNAMEDBUFFERDATAEXTPROC) (
	GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const GLvoid * data);
typedef void (GLAPIENTRY * PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC) (
	GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const GLvoid * data);

PFNGLCLEARBUFFERDATAPROC glClearBufferData(0);
PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData(0);
PFNGLCLEARNAMEDBUFFERDATAEXTPROC glClearNamedBufferDataEXT(0);
PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC glClearNamedBufferSubDataEXT(0);

// GL_ARB_multi_draw_indirect
typedef void (GLAPIENTRY * PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride);
typedef void (GLAPIENTRY * PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void* indirect, GLsizei primcount, GLsizei stride);

PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect(0);
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect(0);

// GL_ARB_invalidate_subdata

typedef void (GLAPIENTRY * PFNGLINVALIDATETEXSUBIMAGEPROC) (
	GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (GLAPIENTRY * PFNGLINVALIDATETEXIMAGEPROC) (
	GLuint texture, GLint level);

PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage(0);
PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage(0);
/*
    void InvalidateBufferSubData(uint buffer, intptr offset, sizeiptr length);
    void InvalidateBufferData(uint buffer);

    void InvalidateFramebuffer(enum target, 
                               sizei numAttachments, 
                               const enum *attachments);
    void InvalidateSubFramebuffer(enum target, 
                                  sizei numAttachments, 
                                  const enum *attachments,
                                  int x, int y, sizei width, sizei height);
*/
#endif // WIN32

namespace glf
{
	inline void swapBuffers()
	{
		glutSwapBuffers();
		glGetError(); // 'glutSwapBuffers' generates an here with OpenGL 3 > core profile ... :/
	}

	inline int version(int Major, int Minor)
	{
		return Major * 100 + Minor * 10;
	}

#if !defined(__APPLE__)
	inline bool checkGLVersion(GLint MajorVersionRequire, GLint MinorVersionRequire)
	{
		GLint MajorVersionContext = 0;
		GLint MinorVersionContext = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &MajorVersionContext);
		glGetIntegerv(GL_MINOR_VERSION, &MinorVersionContext);
		return glf::version(MajorVersionContext, MinorVersionContext) 
			>= glf::version(MajorVersionRequire, MinorVersionRequire);
	}

	inline bool checkExtension(char const * String)
	{
		GLint ExtensionCount = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &ExtensionCount);
		for(GLint i = 0; i < ExtensionCount; ++i)
			if(std::string((char const*)glGetStringi(GL_EXTENSIONS, i)) == std::string(String))
				return true;
		return false;
	}
#endif

	inline void init()
	{
#if (defined(WIN32))
		glewInit();
		glGetError();
		
		//glTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC)glutGetProcAddress("glTextureStorage2DEXT");
		glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)glutGetProcAddress("glDebugMessageControlARB");
		glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)glutGetProcAddress("glDebugMessageCallbackARB");
		glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)glutGetProcAddress("glDebugMessageInsertARB");

		//assert(glTextureStorage2DEXT);
#endif
	}

	inline bool saveBinary
	(
		std::string const & Filename, 
		GLenum const & Format,
		std::vector<glm::byte> const & Data,
		GLint const & Size
	)
	{
		FILE* File = fopen(Filename.c_str(), "wb");

		if(File)
		{
			fwrite(&Format, sizeof(GLenum), 1, File);
			fwrite(&Size, sizeof(Size), 1, File);
			fwrite(&Data[0], Size, 1, File);
			fclose(File);
			return true;
		}
		return false;
	}

	inline bool loadBinary
	(
		std::string const & Filename,
		GLenum & Format,
		std::vector<glm::byte> & Data,
		GLint & Size
	)
	{
		FILE* File = fopen(Filename.c_str(), "rb");

		if(File)
		{
			fread(&Format, sizeof(GLenum), 1, File);
			fread(&Size, sizeof(Size), 1, File);
			Data.resize(Size);
			fread(&Data[0], Size, 1, File);
			fclose(File);
			return true;
		}
		return false;
	}

	inline std::string loadFile(std::string const & Filename)
	{
		std::ifstream stream(Filename.c_str(), std::ios::in);

		if(!stream.is_open())
			return "";

		std::string Line = "";
		std::string Text = "";

		while(getline(stream, Line))
			Text += "\n" + Line;

		stream.close();

		return Text;
	}

	inline bool checkError(const char* Title)
	{
		int Error;
		if((Error = glGetError()) != GL_NO_ERROR)
		{
			std::string ErrorString;
			switch(Error)
			{
			case GL_INVALID_ENUM:
				ErrorString = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				ErrorString = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				ErrorString = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				ErrorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			case GL_OUT_OF_MEMORY:
				ErrorString = "GL_OUT_OF_MEMORY";
				break;
			default:
				ErrorString = "UNKNOWN";
				break;
			}
			fprintf(stdout, "OpenGL Error(%s): %s\n", ErrorString.c_str(), Title);
		}
		return Error == GL_NO_ERROR;
	}

#if !defined(__APPLE__)
	inline bool checkFramebuffer(GLuint FramebufferName)
	{
		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch(Status)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_UNDEFINED");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_UNSUPPORTED");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
			break;
		}

		return Status != GL_FRAMEBUFFER_COMPLETE;
	}
#endif
	inline bool validateProgram(GLuint ProgramName)
	{
		if(!ProgramName)
			return false;

		glValidateProgram(ProgramName);
		GLint Result = GL_FALSE;
		glGetProgramiv(ProgramName, GL_VALIDATE_STATUS, &Result);

		if(Result == GL_FALSE)
		{
			fprintf(stdout, "Validate program\n");
			int InfoLogLength;
			glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if(InfoLogLength > 0)
			{
				std::vector<char> Buffer(InfoLogLength);
				glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
				fprintf(stdout, "%s\n", &Buffer[0]);
			}
		}

		return Result == GL_TRUE;
	}

	inline bool checkProgram(GLuint ProgramName)
	{
		if(!ProgramName)
			return false;

		GLint Result = GL_FALSE;
		glGetProgramiv(ProgramName, GL_LINK_STATUS, &Result);

		fprintf(stdout, "Linking program\n");
		int InfoLogLength;
		glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if(InfoLogLength > 0)
		{
			std::vector<char> Buffer(std::max(InfoLogLength, int(1)));
			glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
			fprintf(stdout, "%s\n", &Buffer[0]);
		}

		return Result == GL_TRUE;
	}

	inline bool checkShader(GLuint ShaderName, const char* Source)
	{
		if(!ShaderName)
			return false;

		GLint Result = GL_FALSE;
		glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Result);

		fprintf(stdout, "Compiling shader\n%s...\n", Source);
		int InfoLogLength;
		glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if(InfoLogLength > 0)
		{
			std::vector<char> Buffer(InfoLogLength);
			glGetShaderInfoLog(ShaderName, InfoLogLength, NULL, &Buffer[0]);
			fprintf(stdout, "%s\n", &Buffer[0]);
		}

		return Result == GL_TRUE;
	}

	inline GLuint createShader
	(
		GLenum Type,
		std::string const & Source
	)
	{
		bool Validated = true;
		GLuint Name = 0;

		if(!Source.empty())
		{
			std::string SourceContent = glf::loadFile(Source);
			char const * SourcePointer = SourceContent.c_str();
			Name = glCreateShader(Type);
			glShaderSource(Name, 1, &SourcePointer, NULL);
			glCompileShader(Name);
			Validated = glf::checkShader(Name, SourcePointer);
		}

		return Name;
	}

	#if !defined(__APPLE__)
    static void GLAPIENTRY debugOutput
	(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		GLvoid* userParam
	)
	{
		//FILE* f;
		//f = fopen("debug_output.txt","a");
		//if(f)
		{
			char debSource[32], debType[32], debSev[32];
			bool Error(false);

			if(source == GL_DEBUG_SOURCE_API_ARB)
				strcpy(debSource, "OpenGL");
			else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
				strcpy(debSource, "Windows");
			else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
				strcpy(debSource, "Shader Compiler");
			else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
				strcpy(debSource, "Third Party");
			else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
				strcpy(debSource, "Application");
			else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
				strcpy(debSource, "Other");
 
			if(type == GL_DEBUG_TYPE_ERROR_ARB)
				strcpy(debType, "error");
			else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
				strcpy(debType, "deprecated behavior");
			else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
				strcpy(debType, "undefined behavior");
			else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
				strcpy(debType, "portability");
			else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
				strcpy(debType, "performance");
			else if(type == GL_DEBUG_TYPE_OTHER_ARB)
				strcpy(debType, "message");
 
			if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
			{
				strcpy(debSev, "high");
				Error = true;
			}
			else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
				strcpy(debSev, "medium");
			else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
				strcpy(debSev, "low");

			 fprintf(stderr,"%s: %s(%s) %d: %s\n", debSource, debType, debSev, id, message);
			 assert(!Error);
			 //fclose(f);
		}
	}
/*
	void checkDebugOutput()
	{
		   unsigned int count = 10; // max. num. of messages that will be read from the log
		   int bufsize = 2048;
	 
		   unsigned int* sources      = new unsigned int[count];
		   unsigned int* types        = new unsigned int[count];
		   unsigned int* ids   = new unsigned int[count];
		   unsigned int* severities = new unsigned int[count];
		   int* lengths = new int[count];
	 
		   char* messageLog = new char[bufsize];
	 
		   unsigned int retVal = glGetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
		   if(retVal > 0)
		   {
				 unsigned int pos = 0;
				 for(unsigned int i=0; i<retVal; i++)
				 {
						debugOutput(sources[i], types[i], ids[i], severities[i], NULL, &messageLog[pos], NULL);
						pos += lengths[i];
				  }
		   }
		   delete [] sources;
		   delete [] types;
		   delete [] ids;
		   delete [] severities;
		   delete [] lengths;
		   delete [] messageLog;
	}
*/
#endif
	static void keyboard(unsigned char key, int x, int y)
	{
		switch(key) 
		{
		case 27:
			end();
			exit(0);

			//exit(end());
			break;
		}
	}

	static void mouse(int Button, int State, int x, int y)
	{
		switch(State)
		{
			case GLUT_DOWN:
			{
				Window.MouseOrigin = Window.MouseCurrent = glm::ivec2(x, y);
				switch(Button)
				{
					case GLUT_LEFT_BUTTON:
					{
						Window.MouseButtonFlags |= glf::MOUSE_BUTTON_LEFT;
						Window.TranlationOrigin = Window.TranlationCurrent;
					}
					break;
					case GLUT_MIDDLE_BUTTON:
					{
						Window.MouseButtonFlags |= glf::MOUSE_BUTTON_MIDDLE;
					}
					break;
					case GLUT_RIGHT_BUTTON:
					{
						Window.MouseButtonFlags |= glf::MOUSE_BUTTON_RIGHT;
						Window.RotationOrigin = Window.RotationCurrent;
					}
					break;
				}
			}
			break;
			case GLUT_UP:
			{
				switch(Button)
				{
					case GLUT_LEFT_BUTTON:
					{
						Window.TranlationOrigin += (Window.MouseCurrent - Window.MouseOrigin) / 10.f;
						Window.MouseButtonFlags &= ~glf::MOUSE_BUTTON_LEFT;
					}
					break;
					case GLUT_MIDDLE_BUTTON:
					{
						Window.MouseButtonFlags &= ~glf::MOUSE_BUTTON_MIDDLE;
					}
					break;
					case GLUT_RIGHT_BUTTON:
					{
						Window.RotationOrigin += Window.MouseCurrent - Window.MouseOrigin;
						Window.MouseButtonFlags &= ~glf::MOUSE_BUTTON_RIGHT;
					}
					break;
				}
			}
			break;
		}
	}

	static void reshape(int w, int h)
	{
		Window.Size = glm::ivec2(w, h);
	}

	static void idle()
	{
#if defined(WIN32)
		glutPostRedisplay();
#endif
	}

	static void close()
	{
		exit(end() ? 0 : 1);
	}

	static void motion(int x, int y)
	{
		Window.MouseCurrent = glm::ivec2(x, y);
		Window.TranlationCurrent = Window.MouseButtonFlags & glf::MOUSE_BUTTON_LEFT ? Window.TranlationOrigin + (Window.MouseCurrent - Window.MouseOrigin) / 10.f : Window.TranlationOrigin;
		Window.RotationCurrent = Window.MouseButtonFlags & glf::MOUSE_BUTTON_RIGHT ? Window.RotationOrigin + (Window.MouseCurrent - Window.MouseOrigin) : Window.RotationOrigin;
	}

	static void displayProxy()
	{
		static int FrameID = 0;
		++FrameID;
#ifdef GLF_AUTO_STATUS
		if(FrameID > 10)
			exit(end() ? 0 : 1);
#endif//GLF_AUTO_STATUS
		display();
	}

	inline int run
	(
		int argc, char* argv[], 
		glm::ivec2 const & Size, 
		int Profile,
		int Major, int Minor
	)
	{
		glutInitWindowSize(Size.x, Size.y);
		glutInitWindowPosition(64, 64);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);// | GLUT_MULTISAMPLE);

		int WindowHandle = glutCreateWindow(argv[0]);
#if !defined(__APPLE__)
		glewInit();
#endif//__APPLE__
		glutDestroyWindow(WindowHandle);

#if !defined(__APPLE__)
		glutInitContextVersion(Major, Minor);
		if(Profile == WGL_CONTEXT_ES2_PROFILE_BIT_EXT)
			glutInitContextProfile(GLUT_ES_PROFILE);
		else if(glf::version(Major, Minor) >= 320)
		{
			glutInitContextProfile(Profile); // GLUT_COMPATIBILITY_PROFILE GLUT_CORE_PROFILE
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
		}
#endif//__APPLE__
		
		glutCreateWindow(argv[0]);
		init();

		if(begin())
		{
			glutDisplayFunc(displayProxy); 
			glutReshapeFunc(glf::reshape);
			glutMouseFunc(glf::mouse);
			glutMotionFunc(glf::motion);
			glutKeyboardFunc(glf::keyboard);
			glutIdleFunc(glf::idle);
#if !defined(__APPLE__)
			glutCloseFunc(glf::close);
			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
#endif//__APPLE__
			glutMainLoop();

			return 0;
		}

		return 1;
	}

	bool validateVAO(GLuint VertexArrayName, std::vector<glf::vertexattrib> const & Expected)
	{
		bool Success = true;

		GLint MaxVertexAttrib(0);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttrib);

		glBindVertexArray(VertexArrayName);
		for(GLuint AttribLocation = 0; AttribLocation < glm::min(GLuint(MaxVertexAttrib), GLuint(Expected.size())); ++AttribLocation)
		{
			glf::vertexattrib VertexAttrib;
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &VertexAttrib.Enabled);
			//glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &VertexAttrib.Binding);
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_SIZE, &VertexAttrib.Size);
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &VertexAttrib.Stride);
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_TYPE, &VertexAttrib.Type);
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &VertexAttrib.Normalized);
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_INTEGER, &VertexAttrib.Integer);
			//glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_LONG, &VertexAttrib.Long);
			glGetVertexAttribiv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &VertexAttrib.Divisor);
			glGetVertexAttribPointerv(AttribLocation, GL_VERTEX_ATTRIB_ARRAY_POINTER, &VertexAttrib.Pointer);
			Success = Success && (VertexAttrib == Expected[AttribLocation]);
			assert(Success);
		}
		glBindVertexArray(0);

		return Success;
	}

}//namespace glf
