#include <SDL.h>
/*
#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

//////////////
// OpenGL 3.0
#ifdef WIN32

#	define GL_TEXTURE_RECTANGLE GL_TEXTURE_RECTANGLE_ARB
#	define GL_MAX_RECTANGLE_TEXTURE_SIZE GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB

typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);

typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);

//////////////
// OpenGL 3.1

#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_UNIFORM_BUFFER_BINDING         0x8A28
#define GL_UNIFORM_BUFFER_START           0x8A29
#define GL_UNIFORM_BUFFER_SIZE            0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS    0x8A2C
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS    0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE         0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_UNIFORM_TYPE                   0x8A37
#define GL_UNIFORM_SIZE                   0x8A38
#define GL_UNIFORM_NAME_LENGTH            0x8A39
#define GL_UNIFORM_BLOCK_INDEX            0x8A3A
#define GL_UNIFORM_OFFSET                 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#define GL_UNIFORM_BLOCK_BINDING          0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE        0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH      0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX                  0xFFFFFFFFu

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint index);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniformCount, const GLchar* *uniformNames, GLuint *uniformIndices);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = 0;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = 0;
PFNGLTEXBUFFERPROC glTexBuffer = 0;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = 0;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = 0;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = 0;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = 0;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = 0;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = 0;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = 0;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = 0;

// OpenGL 3.2

typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices, GLint basevertex);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei* count, GLenum type, GLvoid**indices, GLsizei primcount, GLint *basevertex);

PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = 0;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex = 0;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex = 0;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex = 0;

#endif//WIN32
*/

#ifdef WIN32
	#ifndef APIENTRY
	#define APIENTRY
	#endif
	#ifndef APIENTRYP
	#define APIENTRYP APIENTRY *
	#endif
	#ifndef GLAPI
	#define GLAPI extern
	#endif

#ifndef GL_ARB_texture_swizzle
#define GL_ARB_texture_swizzle 1
	#define GL_TEXTURE_SWIZZLE_R              0x8E42
	#define GL_TEXTURE_SWIZZLE_G              0x8E43
	#define GL_TEXTURE_SWIZZLE_B              0x8E44
	#define GL_TEXTURE_SWIZZLE_A              0x8E45
	#define GL_TEXTURE_SWIZZLE_RGBA           0x8E46
#endif

#ifndef GL_ARB_occlusion_query2
#define GL_ARB_occlusion_query2 1
	#define GL_ANY_SAMPLES_PASSED             0x8C2F
#endif

#ifndef GL_ARB_sampler_objects
#define GL_ARB_sampler_objects 1
	typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
	typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
	typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
	typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLenum unit, GLuint sampler);
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
	typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, const GLuint *param);
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
	typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);

	PFNGLGENSAMPLERSPROC glGenSamplers = 0;
	PFNGLDELETESAMPLERSPROC glDeleteSamplers = 0;
	PFNGLISSAMPLERPROC glIsSampler = 0;
	PFNGLBINDSAMPLERPROC glBindSampler = 0;
	PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = 0;
	PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = 0;
	PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = 0;
	PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = 0;
	PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv = 0;
	PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv = 0;
	PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = 0;
	PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv = 0;
	PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = 0;
	PFNGLGETSAMPLERPARAMETERIFVPROC glGetSamplerParameterIfv = 0;
#endif//GL_ARB_sampler_objects

#ifndef GL_ARB_timer_query
#define GL_ARB_timer_query 1

#define GL_TIME_ELAPSED                   0x88BF
#define GL_TIMESTAMP                      0x8E28

	typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
	typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
	typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);

	PFNGLQUERYCOUNTERPROC glQueryCounter = 0;
	PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v = 0;
	PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = 0;
#endif

	typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORARBPROC) (GLuint index, GLuint divisor);

	PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisor = 0;

#endif//WIN32

namespace glf{
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
#endif
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
