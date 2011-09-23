#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

bool check();
bool begin();
bool end();
void display();
/*
typedef void (GLAPIENTRY * PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride);
typedef void (GLAPIENTRY * PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const GLvoid* indirect, GLsizei primcount, GLsizei stride);

PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirectAMD = 0;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirectAMD = 0;

// GL_ARB_base_instance
typedef void (GLAPIENTRY * PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance);
typedef void (GLAPIENTRY * PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLuint baseinstance);
typedef void (GLAPIENTRY * PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLint basevertex, GLuint baseinstance);

PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance = 0;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance = 0;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance = 0;

// GL_ARB_transform_feedback_instanced
typedef void  (GLAPIENTRY * PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum mode, GLuint id, GLsizei primcount);
typedef void  (GLAPIENTRY * PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDSTREAMPROC) (GLenum mode, GLuint id, GLuint stream, GLsizei primcount);

PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced = 0;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDSTREAMPROC glDrawTransformFeedbackStreamInstanced = 0;

// GL_ARB_internalformat_query
typedef void (GLAPIENTRY * PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);

PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = 0;

// GL_ARB_shader_atomic_counters
typedef void (GLAPIENTRY * PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);

PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv = 0;

#define GL_ATOMIC_COUNTER_BUFFER							0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING                    0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START                      0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE                       0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE                  0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS     0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES        0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER          0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER    0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER        0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER        0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS                0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS          0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS       0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS              0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS              0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS              0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS                       0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS                 0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS              0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS                     0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS                     0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS                     0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE                   0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS               0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS                    0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX              0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER                      0x92DB

// GL_ARB_map_buffer_alignment
#define GL_MINIMUM_MAP_BUFFER_ALIGNMENT						0x90BC

// GL_ARB_compressed_texture_pixel_storage
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH                    0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT                   0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH                    0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE                     0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH                      0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT                     0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH                      0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE                       0x912E

// GL_ARB_shader_image_load_store
typedef void (GLAPIENTRY * PFNGLBINDIMAGETEXTUREPROC) (GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (GLAPIENTRY * PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);

PFNGLBINDIMAGETEXTUREPROC glBindImageTexture = 0;
PFNGLMEMORYBARRIERPROC glMemoryBarrier = 0;

#define GL_MAX_IMAGE_UNITS                                 0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS   0x8F39
#define GL_MAX_IMAGE_SAMPLES                               0x906D
#define GL_IMAGE_BINDING_NAME                              0x8F3A
#define GL_IMAGE_BINDING_LEVEL                             0x8F3B
#define GL_IMAGE_BINDING_LAYERED                           0x8F3C
#define GL_IMAGE_BINDING_LAYER                             0x8F3D
#define GL_IMAGE_BINDING_ACCESS                            0x8F3E
#define GL_IMAGE_BINDING_FORMAT                            0x906E
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT                 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT                       0x00000002
#define GL_UNIFORM_BARRIER_BIT                             0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT                       0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT                 0x00000020
#define GL_COMMAND_BARRIER_BIT                             0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT                        0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT                      0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT                       0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT                         0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT                  0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT                      0x00001000
#define GL_ALL_BARRIER_BITS                                0xFFFFFFFF
#define GL_IMAGE_1D                                        0x904C
#define GL_IMAGE_2D                                        0x904D
#define GL_IMAGE_3D                                        0x904E
#define GL_IMAGE_2D_RECT                                   0x904F
#define GL_IMAGE_CUBE                                      0x9050
#define GL_IMAGE_BUFFER                                    0x9051
#define GL_IMAGE_1D_ARRAY                                  0x9052
#define GL_IMAGE_2D_ARRAY                                  0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY                            0x9054
#define GL_IMAGE_2D_MULTISAMPLE                            0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY                      0x9056
#define GL_INT_IMAGE_1D                                    0x9057
#define GL_INT_IMAGE_2D                                    0x9058
#define GL_INT_IMAGE_3D                                    0x9059
#define GL_INT_IMAGE_2D_RECT                               0x905A
#define GL_INT_IMAGE_CUBE                                  0x905B
#define GL_INT_IMAGE_BUFFER                                0x905C
#define GL_INT_IMAGE_1D_ARRAY                              0x905D
#define GL_INT_IMAGE_2D_ARRAY                              0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY                        0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE                        0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY                  0x9061
#define GL_UNSIGNED_INT_IMAGE_1D                           0x9062
#define GL_UNSIGNED_INT_IMAGE_2D                           0x9063
#define GL_UNSIGNED_INT_IMAGE_3D                           0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT                      0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE                         0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER                       0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY                     0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY                     0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY               0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE               0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY         0x906C
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE                 0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE              0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS             0x90C9

// GL_ARB_texture_storage
typedef void (GLAPIENTRY * PFNGLTEXSTORAGE1DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (GLAPIENTRY * PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (GLAPIENTRY * PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (GLAPIENTRY * PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);

PFNGLTEXSTORAGE1DPROC glTexStorage1D = 0;
PFNGLTEXSTORAGE2DPROC glTexStorage2D = 0;
PFNGLTEXSTORAGE3DPROC glTexStorage3D = 0;
PFNGLTEXTURESTORAGE1DEXTPROC glTextureStorage1DEXT = 0;
PFNGLTEXTURESTORAGE2DEXTPROC glTextureStorage2DEXT = 0;
PFNGLTEXTURESTORAGE3DEXTPROC glTextureStorage3DEXT = 0;

#define GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#define GL_ALPHA8_EXT                     0x803C
#define GL_LUMINANCE8_EXT                 0x8040
#define GL_LUMINANCE8_ALPHA8_EXT          0x8045
*/
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
		std::vector<char> Buffer(std::max(InfoLogLength, int(1)));
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
				strcpy(debSev, "high");
			else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
				strcpy(debSev, "medium");
			else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
				strcpy(debSev, "low");

			 fprintf(stderr,"%s: %s(%s) %d: %s\n", debSource, debType, debSev, id, message);
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
		if(glf::version(Major, Minor) >= 320)
		{
#if defined(WIN32)
			glutInitContextProfile(GLUT_CORE_PROFILE); // GLUT_COMPATIBILITY_PROFILE
#else
			glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // GLUT_COMPATIBILITY_PROFILE
#endif
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

}//namespace glf
