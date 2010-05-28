#include <SDL.h>

#ifdef WIN32
	PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisor = 0;
#endif//WIN32

namespace glf
{
	namespace detail
	{
		int const WINDOW_WIDTH = 640;
		int const WINDOW_HEIGHT = 480;
		bool const WINDOW_FULLSCREEN = false;

		SDL_Surface* g_Surface = 0;

		inline void CreateWindowSDL
		(
			char const * Name, 
			int Width, 
			int Height, 
			bool Fullscreen,
			glm::uint32 VersionMajor,
			glm::uint32 VersionMinor
		)
		{
			if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
				return;

			unsigned int VideoFlags = SDL_OPENGL | SDL_DOUBLEBUF;
			//if(Fullscreen)
			//	VideoFlags |= SDL_FULLSCREEN;

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
			SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);
			//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, GL_TRUE);
			//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
			if(VersionMajor)
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, VersionMajor);
			if(VersionMinor)
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, VersionMinor);

			//SDL_GL_ACCELERATED_VISUAL,

			if((g_Surface = SDL_SetVideoMode(Width, Height, 32, VideoFlags)) == 0)
				return;

			SDL_WM_SetCaption(Name, Name);

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
			glVertexAttribDivisorARB = (PFNGLVERTEXATTRIBDIVISORARBPROC)glfGetProcAddress("glVertexAttribDivisor");

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

		inline void DeleteWindowSDL()
		{
			if(g_Surface)
			{
				SDL_FreeSurface(g_Surface);
				g_Surface = NULL;
			}
			SDL_Quit();
		}

		inline void SwapBufferSDL()
		{
			SDL_GL_SwapBuffers();
		}

	}//namespace detail

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

	inline window::window
	(
		std::string const & Title,
		glm::ivec2 const & WindowSize
	) :
		MouseButtonFlags(0),
		MouseCurrent(WindowSize / 2),
		MouseOrigin(WindowSize / 2),
		RotationCurrent(0.f),
		RotationOrigin(0.f),
		TranlationOrigin(0.f, 4.f),
		TranlationCurrent(0.f, 4.f),
		IndexCurrent(0),
		IndexMax(10),
		Title(Title),
		WindowSize(WindowSize)
	{
		detail::CreateWindowSDL(
			Title.c_str(), 
			WindowSize.x, WindowSize.y, 
			detail::WINDOW_FULLSCREEN, 
			0, 0);
	}

	inline window::window
	(
		std::string const & Title,
		glm::ivec2 const & WindowSize,
		glm::uint32 VersionMajor,
		glm::uint32 VersionMinor
	) :
		MouseButtonFlags(0),
		MouseCurrent(WindowSize / 2),
		MouseOrigin(WindowSize / 2),
		RotationCurrent(0.f),
		RotationOrigin(0.f),
		TranlationOrigin(0.f, 4.f),
		TranlationCurrent(0.f, 4.f),
		IndexCurrent(0),
		IndexMax(10),
		Title(Title),
		WindowSize(WindowSize)
	{
		detail::CreateWindowSDL(
			Title.c_str(), 
			WindowSize.x, WindowSize.y, 
			detail::WINDOW_FULLSCREEN,
			VersionMajor, VersionMinor);
	}

	inline window::~window()
	{
		detail::DeleteWindowSDL();
	}

	inline void window::onMouseMove(glm::vec2 const & MouseCurrent)
	{
		this->MouseCurrent = MouseCurrent;
		this->TranlationCurrent = MouseButtonFlags & MOUSE_BUTTON_LEFT ? TranlationOrigin + (MouseCurrent - MouseOrigin) / 10.f : TranlationOrigin;
		this->RotationCurrent = MouseButtonFlags & MOUSE_BUTTON_RIGHT ? RotationOrigin + (MouseCurrent - MouseOrigin) : RotationOrigin;
	}

	inline void window::onMouseDown(mouse_button MouseButton)
	{
		MouseButtonFlags |= MouseButton;

		switch(MouseButton)
		{
		default:
			break;
		case MOUSE_BUTTON_LEFT:
		case MOUSE_BUTTON_RIGHT:
		case MOUSE_BUTTON_MIDDLE:
			MouseOrigin = MouseCurrent;
			break;
		}
	}

	inline void window::onMouseUp(mouse_button MouseButton)
	{
		MouseButtonFlags &= ~MouseButton;

		switch(MouseButton)
		{
		default:
			break;
		case MOUSE_BUTTON_LEFT:
			TranlationOrigin += (MouseCurrent - MouseOrigin) / 10.f;
			break;
		case MOUSE_BUTTON_RIGHT:
			RotationOrigin += MouseCurrent - MouseOrigin;
			break;
		case MOUSE_BUTTON_MIDDLE:
			++IndexCurrent;
			IndexCurrent %= IndexMax;
			break;
		}
	}

	inline bool window::run()
	{
		bool Exit = false;
		while(!Exit)
		{
			SDL_Event Event;
			while(SDL_PollEvent(&Event))
			{
				switch(Event.type)
				{
				case SDL_QUIT:
				case SDL_KEYUP:
					Exit = true;
					break;
				case SDL_MOUSEMOTION:
					{
					SDL_MouseMotionEvent* MotionEvent = (SDL_MouseMotionEvent*) &Event;
					onMouseMove(glm::vec2(float(MotionEvent->x), float(detail::WINDOW_HEIGHT - MotionEvent->y)));
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(((SDL_MouseButtonEvent*)&Event)->button)
					{
					default:
						break;
					case SDL_BUTTON_LEFT:
						onMouseDown(MOUSE_BUTTON_LEFT);
						break;
					case SDL_BUTTON_RIGHT:
						onMouseDown(MOUSE_BUTTON_RIGHT);
						break;
					case SDL_BUTTON_MIDDLE:
						onMouseDown(MOUSE_BUTTON_MIDDLE);
						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(((SDL_MouseButtonEvent*)&Event)->button)
					{
					default:
						break;
					case SDL_BUTTON_LEFT:
						onMouseUp(MOUSE_BUTTON_LEFT);
						break;
					case SDL_BUTTON_RIGHT:
						onMouseUp(MOUSE_BUTTON_RIGHT);
						break;
					case SDL_BUTTON_MIDDLE:
						onMouseUp(MOUSE_BUTTON_MIDDLE);
						break;
					}
					break;
				break;
				}
			}

			render();

			detail::SwapBufferSDL();
		}

		return Exit;
	}

}//namespace glf
