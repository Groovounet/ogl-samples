#include <GL/freeglut.h>

#ifdef WIN32
	PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisor = 0;
#endif//WIN32

bool check();
bool begin();
bool end();
void display();

namespace glf
{
	inline void swapBuffers()
	{
		glutSwapBuffers();
	}

	inline void initFunc()
	{
#ifdef WIN32
		glewInit();
		glGetError();

		// Load OpenGL 3.0 functions
		glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)glfGetProcAddress("glBindBufferBase");
		glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)glfGetProcAddress("glBindFragDataLocation");
		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfGetProcAddress("glGenerateMipmap");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glfGetProcAddress("glDeleteVertexArrays");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glfGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glfGetProcAddress("glBindVertexArray");
		glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glfGetProcAddress("glGenFramebuffers");
		glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glfGetProcAddress("glBindFramebuffer");
		glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glfGetProcAddress("glFramebufferTexture2D");
		glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)glfGetProcAddress("glCheckFramebufferStatus");
		glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glfGetProcAddress("glDeleteFramebuffers");
		glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)glfGetProcAddress("glMapBufferRange");
		glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)glfGetProcAddress("glFlushMappedBufferRange");
		glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glfGetProcAddress("glGenRenderbuffers");
		glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glfGetProcAddress("glBindRenderbuffer");
		glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glfGetProcAddress("glRenderbufferStorage");
		glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glfGetProcAddress("glFramebufferRenderbuffer");
		glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)glfGetProcAddress("glBlitFramebuffer");
		glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glfGetProcAddress("glDeleteRenderbuffers");
		glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)glfGetProcAddress("glRenderbufferStorageMultisample");
		glColorMaski = (PFNGLCOLORMASKIPROC)glfGetProcAddress("glColorMaski");
		glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)glfGetProcAddress("glGetBooleani_v");
		glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)glfGetProcAddress("glGetIntegeri_v");
		glEnablei = (PFNGLENABLEIPROC)glfGetProcAddress("glEnablei");
		glDisablei = (PFNGLDISABLEIPROC)glfGetProcAddress("glDisablei");

		// Load OpenGL 3.1 functions
		glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)glfGetProcAddress("glDrawArraysInstanced");
		glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)glfGetProcAddress("glDrawElementsInstanced");
		glTexBuffer = (PFNGLTEXBUFFERPROC)glfGetProcAddress("glTexBuffer");
		glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)glfGetProcAddress("glPrimitiveRestartIndex");
		glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)glfGetProcAddress("glGetUniformIndices");
		glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)glfGetProcAddress("glGetActiveUniformsiv");
		glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)glfGetProcAddress("glGetActiveUniformName");
		glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)glfGetProcAddress("glGetUniformBlockIndex");
		glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)glfGetProcAddress("glGetActiveUniformBlockiv");
		glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)glfGetProcAddress("glGetActiveUniformBlockName");
		glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)glfGetProcAddress("glUniformBlockBinding");

		// Load OpenGL 3.2 functions
		glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)glfGetProcAddress("glDrawElementsBaseVertex");
		glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)glfGetProcAddress("glDrawElementsBaseVertex");
		glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)glfGetProcAddress("glDrawRangeElementsBaseVertex");
		glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)glfGetProcAddress("glMultiDrawElementsBaseVertex");

		// Load OpenGL 3.3 functions
		glGenSamplers = (PFNGLGENSAMPLERSPROC)glfGetProcAddress("glGenSamplers");
		glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)glfGetProcAddress("glDeleteSamplers");
		glIsSampler = (PFNGLISSAMPLERPROC)glfGetProcAddress("glIsSampler");
		glBindSampler = (PFNGLBINDSAMPLERPROC)glfGetProcAddress("glBindSampler");
		glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)glfGetProcAddress("glSamplerParameteri");
		glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)glfGetProcAddress("glSamplerParameteriv");
		glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)glfGetProcAddress("glSamplerParameterf");
		glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)glfGetProcAddress("glSamplerParameterfv");
		glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)glfGetProcAddress("glSamplerParameterIiv");
		glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)glfGetProcAddress("glSamplerParameterIuiv");
		glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)glfGetProcAddress("glGetSamplerParameteriv");
		glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)glfGetProcAddress("glGetSamplerParameterIiv");
		glGetSamplerParameterfv =   (PFNGLGETSAMPLERPARAMETERFVPROC)glfGetProcAddress("glGetSamplerParameterfv");
		glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)glfGetProcAddress("glGetSamplerParameterIuiv");
		glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORARBPROC)glfGetProcAddress("glVertexAttribDivisor");

		// Load OpenGL 4.0 functions
		glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)glfGetProcAddress("glBindTransformFeedback");
		glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)glfGetProcAddress("glDeleteTransformFeedbacks");
		glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)glfGetProcAddress("glGenTransformFeedbacks");
		glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)glfGetProcAddress("glIsTransformFeedback");
		glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)glfGetProcAddress("glPauseTransformFeedback");
		glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)glfGetProcAddress("glResumeTransformFeedback");
		glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)glfGetProcAddress("glDrawTransformFeedback");
		glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)glfGetProcAddress("glPatchParameteri");
		glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)glfGetProcAddress("glPatchParameterfv");
		glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)glfGetProcAddress("glGetActiveSubroutineName");
		glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)glfGetProcAddress("glGetActiveSubroutineUniformName");
		glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)glfGetProcAddress("glGetActiveSubroutineUniformiv");
		glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)glfGetProcAddress("glGetProgramStageiv");
		glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)glfGetProcAddress("glGetSubroutineIndex");
		glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)glfGetProcAddress("glGetSubroutineUniformLocation");
		glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)glfGetProcAddress("glGetUniformSubroutineuiv");
		glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)glfGetProcAddress("glUniformSubroutinesuiv");
		glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)glfGetProcAddress("glDrawArraysIndirect");
		glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)glfGetProcAddress("glDrawElementsIndirect");
		glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)glfGetProcAddress("glBlendEquationSeparatei");
		glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)glfGetProcAddress("glBlendEquationi");
		glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)glfGetProcAddress("glBlendFuncSeparatei");
		glBlendFunci = (PFNGLBLENDFUNCIPROC)glfGetProcAddress("glBlendFunci");
		glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)glfGetProcAddress("glMinSampleShading");
#endif//WIN32
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
			std::vector<char> Buffer(InfoLogLength);
			glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
			fprintf(stdout, "%s\n", &Buffer[0]);
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
		std::vector<char> Buffer(InfoLogLength);
		glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
		fprintf(stdout, "%s\n", &Buffer[0]);

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
		std::vector<char> Buffer(InfoLogLength);
		glGetShaderInfoLog(ShaderName, InfoLogLength, NULL, &Buffer[0]);
		fprintf(stdout, "%s\n", &Buffer[0]);

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

	inline GLuint createProgram
	(
		std::string const & VertShader, 
		std::string const & FragShader
	)
	{
		bool Validated = true;
		GLuint ProgramName = 0;

		// Compile a shader
		GLuint VertexShaderName = 0;
		if(Validated && !VertShader.empty())
		{
			std::string Source0 = glf::loadFile(VertShader);
			char const * Source = Source0.c_str();
			VertexShaderName = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(VertexShaderName, 1, &Source, NULL);
			glCompileShader(VertexShaderName);
			Validated = glf::checkShader(VertexShaderName, Source);
		}

		// Compile a shader
		GLuint FragmentShaderName = 0;
		if(Validated && !FragShader.empty())
		{
			std::string Source0 = glf::loadFile(FragShader);
			char const * Source = Source0.c_str();
			FragmentShaderName = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(FragmentShaderName, 1, &Source, NULL);
			glCompileShader(FragmentShaderName);
			Validated = glf::checkShader(FragmentShaderName, Source);
		}

		// Link a program
		if(Validated)
		{
			ProgramName = glCreateProgram();
			if(VertexShaderName != 0)
				glAttachShader(ProgramName, VertexShaderName);
			if(FragmentShaderName != 0)
				glAttachShader(ProgramName, FragmentShaderName);
			glDeleteShader(VertexShaderName);
			glDeleteShader(FragmentShaderName);
			// Bind fragment output to color buffer 0
			//glBindFragDataLocation(ProgramName, 0, "FragColor");
			//glLinkProgram(ProgramName);
			//Validated = glf::checkProgram(ProgramName);
		}

		return ProgramName;
	}

	inline int version(int Major, int Minor)
	{
		return Major * 100 + Minor * 10;
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		switch(key) 
		{
		case 27:
			exit(0);
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
		glutPostRedisplay();
	}

	static void motion(int x, int y)
	{
		Window.MouseCurrent = glm::ivec2(x, y);
		Window.TranlationCurrent = Window.MouseButtonFlags & glf::MOUSE_BUTTON_LEFT ? Window.TranlationOrigin + (Window.MouseCurrent - Window.MouseOrigin) / 10.f : Window.TranlationOrigin;
		Window.RotationCurrent = Window.MouseButtonFlags & glf::MOUSE_BUTTON_RIGHT ? Window.RotationOrigin + (Window.MouseCurrent - Window.MouseOrigin) : Window.RotationOrigin;
	}

	inline bool run
	(
		int argc, char* argv[], 
		glm::ivec2 const & Size, 
		int Major, int Minor
	)
	{
		glutInitWindowSize(Size.x, Size.y);
		glutInitWindowPosition(64, 64);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
		glutInitContextVersion(Major, Minor);
		if(glf::version(Major, Minor) >= 300)
		{
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
			glutInitContextProfile(GLUT_CORE_PROFILE);
		}

		glutCreateWindow(argv[0]);
		glewInit();
		glGetError();
		//glf::init();

		if(begin())
		{
			glutDisplayFunc(display); 
			glutReshapeFunc(glf::reshape);
			glutMouseFunc(glf::mouse);
			glutMotionFunc(glf::motion);
			glutKeyboardFunc(glf::keyboard);
			glutIdleFunc(glf::idle);

			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

			glutMainLoop();

			end();

			return 0;
		}

		return 1;
	}

}//namespace glf
