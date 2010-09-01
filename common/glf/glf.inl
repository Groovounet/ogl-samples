#include <GL/freeglut.h>

#ifdef WIN32
#	undef APIENTRY
//#	ifndef APIENTRY
#		define APIENTRY
//#	endif
#	ifndef APIENTRYP
#		define APIENTRYP APIENTRY *
#	endif

// Declare OpenGL 4.1 enums
#define GL_VERTEX_SHADER_BIT				0x00000001
#define GL_FRAGMENT_SHADER_BIT				0x00000002
#define GL_GEOMETRY_SHADER_BIT				0x00000004
#define GL_TESS_CONTROL_SHADER_BIT			0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT		0x00000010
#define GL_ALL_SHADER_BITS					0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE				0x8258
#define GL_ACTIVE_PROGRAM					0x8259
#define GL_PROGRAM_PIPELINE_BINDING			0x825A
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT	0x8257
#define GL_PROGRAM_BINARY_LENGTH			0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS		0x87FE
#define GL_PROGRAM_BINARY_FORMATS			0x87FF

// Declare OpenGL 4.1 functions
//typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
/*
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat x);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat x, GLfloat y);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1DPROC) (GLuint program, GLint location, GLdouble x);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2DPROC) (GLuint program, GLint location, GLdouble x, GLdouble y);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3DPROC) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4DPROC) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint x);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint x, GLint y);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint x, GLint y, GLint z);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint x);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint x, GLuint y);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint x, GLuint y, GLuint z);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
*/
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
//typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);

//typedef void (GLAPIENTRY * PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
//typedef void (GLAPIENTRY * PFNGLACTIVESHADERPROGRAM) (GLuint pipeline, GLuint program);
//typedef GLuint (GLAPIENTRY * PFNGLCREATESHADERPROGRAMV) (GLenum type, GLsizei count, const GLchar **strings);
//typedef void (GLAPIENTRY * PFNGLBINDPROGRAMPIPELINE) (GLuint pipeline);
//typedef void (GLAPIENTRY * PFNGLDELETEPROGRAMPIPELINES) (GLsizei n, const GLuint *pipelines);
//typedef void (GLAPIENTRY * PFNGLGENPROGRAMPIPELINES) (GLsizei n, GLuint *pipelines);
//typedef GLboolean (GLAPIENTRY * PFNGLISPROGRAMPIPELINE) (GLuint pipeline);
//typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETERI) (GLuint program, GLenum pname, GLint value);
//typedef void (GLAPIENTRY * PFNGLGETPROGRAMPIPELINEIV) (GLuint pipeline, GLenum pname, GLint *params);
//typedef void (GLAPIENTRY * PFNGLVALIDATEPROGRAMPIPELINE) (GLuint pipeline);
//typedef void (GLAPIENTRY * PFNGLGETPROGRAMPIPELINEINFOLOG) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

typedef void (GLAPIENTRY * PFNGLVIEWPORTARRAYV) (GLuint first, GLsizei count, const GLfloat * v);
typedef void (GLAPIENTRY * PFNGLVIEWPORTINDEXEDF) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (GLAPIENTRY * PFNGLVIEWPORTINDEXEDFV) (GLuint index, const GLfloat * v);
typedef void (GLAPIENTRY * PFNGLSCISSORARRAYV) (GLuint first, GLsizei count, const GLint * v);
typedef void (GLAPIENTRY * PFNGLSCISSORINDEXED) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (GLAPIENTRY * PFNGLSCISSORINDEXEDV) (GLuint index, const GLint * v);
typedef void (GLAPIENTRY * PFNGLDEPTHRANGEARRAYV) (GLuint first, GLsizei count, const GLclampd * v);
typedef void (GLAPIENTRY * PFNGLDEPTHRANGEINDEXED) (GLuint index, GLclampd n, GLclampd f);
typedef void (GLAPIENTRY * PFNGLGETFLOATI_V) (GLenum target, GLuint index, GLfloat *data);
typedef void (GLAPIENTRY * PFNGLGETDOUBLEI_V) (GLenum target, GLuint index, GLdouble *data);

typedef void (GLAPIENTRY * PFNGLGETPROGRAMBINARY) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (GLAPIENTRY * PFNGLPROGRAMBINARY) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
/*
PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer = 0;

PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = 0;
PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv = 0;
PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = 0;
PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv = 0;
PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = 0;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = 0;
PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f = 0;
PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = 0;

PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d = 0;
PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv = 0;
PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d = 0;
PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv = 0;
PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d = 0;
PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv = 0;
PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d = 0;
PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv = 0;

PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = 0;
PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv = 0;
PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i = 0;
PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv = 0;
PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i = 0;
PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv = 0;
PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i = 0;
PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv = 0;

PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui = 0;
PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv = 0;
PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui = 0;
PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv = 0;
PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui = 0;
PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv = 0;
PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui = 0;
PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv = 0;

PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv = 0;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv = 0;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv = 0;

PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv = 0;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv = 0;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv = 0;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv = 0;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv = 0;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv = 0;

PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages = 0;
PFNGLACTIVESHADERPROGRAM glActiveShaderProgram = 0;
PFNGLCREATESHADERPROGRAMV glCreateShaderProgramv = 0;
PFNGLBINDPROGRAMPIPELINE glBindProgramPipeline = 0;
PFNGLDELETEPROGRAMPIPELINES glDeleteProgramPipelines = 0;
PFNGLGENPROGRAMPIPELINES glGenProgramPipelines = 0;
PFNGLISPROGRAMPIPELINE glIsProgramPipeline = 0;
PFNGLPROGRAMPARAMETERI glProgramParameteri = 0;
PFNGLGETPROGRAMPIPELINEIV glGetProgramPipelineiv = 0;
PFNGLVALIDATEPROGRAMPIPELINE glValidateProgramPipeline = 0;
PFNGLGETPROGRAMPIPELINEINFOLOG glGetProgramPipelineInfoLog = 0;

PFNGLVIEWPORTARRAYV glViewportArrayv = 0;
PFNGLVIEWPORTINDEXEDF glViewportIndexedf = 0;
PFNGLVIEWPORTINDEXEDFV glViewportIndexedfv = 0;
PFNGLSCISSORARRAYV glScissorArrayv = 0;
PFNGLSCISSORINDEXED glScissorIndexed = 0;
PFNGLSCISSORINDEXEDV glScissorIndexedv = 0;
PFNGLDEPTHRANGEARRAYV glDepthRangeArrayv = 0;
PFNGLDEPTHRANGEINDEXED glDepthRangeIndexed = 0;
PFNGLGETFLOATI_V glGetFloati_v = 0;
PFNGLGETDOUBLEI_V glGetDoublei_v = 0;

PFNGLGETPROGRAMBINARY glGetProgramBinary = 0;
PFNGLPROGRAMBINARY glProgramBinary = 0;
*/
#ifndef GL_ARB_debug_output
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB               0x8242
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB               0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB              0x9144
#define GL_DEBUG_LOGGED_MESSAGES_ARB                  0x9145
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB       0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_ARB                0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB              0x8245
#define GL_DEBUG_SOURCE_API_ARB                       0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB             0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB           0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB               0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB               0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB                     0x824B
#define GL_DEBUG_TYPE_ERROR_ARB                       0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB         0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB          0x824E
#define GL_DEBUG_TYPE_PORTABILITY_ARB                 0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_ARB                 0x8250
#define GL_DEBUG_TYPE_OTHER_ARB                       0x8251
#define GL_DEBUG_SEVERITY_HIGH_ARB                    0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB                  0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB                     0x9148

typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar* message,
                                        GLvoid* userParam);

typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLARBPROC) (unsigned int source, unsigned int type,
	unsigned int severity, int count, const unsigned int* ids, bool enabled);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTARBPROC) (unsigned int source, unsigned int type,
	unsigned int id, unsigned int severity, int length, const char* buf);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKARBPROC) (GLDEBUGPROCARB callback,
	void* userParam);
typedef unsigned int (APIENTRYP PFNGLGETDEBUGMESSAGELOGARBPROC) (unsigned int count, int bufsize,
	unsigned int* sources,unsigned int* types, unsigned int* ids,
	unsigned int* severities, int* lengths, char* messageLog);
 
extern PFNGLDEBUGMESSAGECONTROLARBPROC  glDebugMessageControlARB;
extern PFNGLDEBUGMESSAGEINSERTARBPROC   glDebugMessageInsertARB;
extern PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB;
extern PFNGLGETDEBUGMESSAGELOGARBPROC   glGetDebugMessageLogARB;
 
PFNGLDEBUGMESSAGECONTROLARBPROC   glDebugMessageControlARB   = 0;
PFNGLDEBUGMESSAGEINSERTARBPROC    glDebugMessageInsertARB    = 0;
PFNGLDEBUGMESSAGECALLBACKARBPROC  glDebugMessageCallbackARB  = 0;
PFNGLGETDEBUGMESSAGELOGARBPROC    glGetDebugMessageLogARB    = 0;

#endif//GL_ARB_debug_output

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
		glGetError(); // 'glutSwapBuffers' generates an here with OpenGL 3 > core profile ... :/
	}

	inline void init()
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
		glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)glfGetProcAddress("glFramebufferTextureLayer");
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
		glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)glfGetProcAddress("glBindBufferBase");
		glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)glfGetProcAddress("glBindBufferRange");
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
		glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)glfGetProcAddress("glDrawElementsInstancedBaseVertex");
		glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)glfGetProcAddress("glDrawRangeElementsBaseVertex");
		glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)glfGetProcAddress("glMultiDrawElementsBaseVertex");
		glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)glfGetProcAddress("glTexImage2DMultisample");
		glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)glfGetProcAddress("glTexImage3DMultisample");

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

		glUniform1d = (PFNGLUNIFORM1DPROC)glfGetProcAddress("glUniform1d");
		glUniform2d = (PFNGLUNIFORM2DPROC)glfGetProcAddress("glUniform2d");
		glUniform3d = (PFNGLUNIFORM3DPROC)glfGetProcAddress("glUniform3d");
		glUniform4d = (PFNGLUNIFORM4DPROC)glfGetProcAddress("glUniform4d");
		glUniform1dv = (PFNGLUNIFORM1DVPROC)glfGetProcAddress("glUniform1dv");
		glUniform2dv = (PFNGLUNIFORM2DVPROC)glfGetProcAddress("glUniform2dv");
		glUniform3dv = (PFNGLUNIFORM3DVPROC)glfGetProcAddress("glUniform3dv");
		glUniform4dv = (PFNGLUNIFORM4DVPROC)glfGetProcAddress("glUniform4dv");
		glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)glfGetProcAddress("glUniformMatrix2dv");
		glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)glfGetProcAddress("glUniformMatrix3dv");
		glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)glfGetProcAddress("glUniformMatrix4dv");
		glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)glfGetProcAddress("glUniformMatrix2x3dv");
		glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)glfGetProcAddress("glUniformMatrix2x4dv");
		glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)glfGetProcAddress("glUniformMatrix3x2dv");
		glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)glfGetProcAddress("glUniformMatrix3x4dv");
		glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)glfGetProcAddress("glUniformMatrix4x2dv");
		glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)glfGetProcAddress("glUniformMatrix4x3dv");

		// Load OpenGL 4.1 functions
		glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)glfGetProcAddress("glVertexAttribLPointer");

		glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)glfGetProcAddress("glProgramUniform1i");
		glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)glfGetProcAddress("glProgramUniform1iv");
		glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)glfGetProcAddress("glProgramUniform2i");
		glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)glfGetProcAddress("glProgramUniform2iv");
		glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)glfGetProcAddress("glProgramUniform3i");
		glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)glfGetProcAddress("glProgramUniform3iv");
		glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)glfGetProcAddress("glProgramUniform4i");
		glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)glfGetProcAddress("glProgramUniform4iv");

		glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)glfGetProcAddress("glProgramUniform1ui");
		glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)glfGetProcAddress("glProgramUniform1uiv");
		glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)glfGetProcAddress("glProgramUniform2ui");
		glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)glfGetProcAddress("glProgramUniform2uiv");
		glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)glfGetProcAddress("glProgramUniform3ui");
		glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)glfGetProcAddress("glProgramUniform3uiv");
		glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)glfGetProcAddress("glProgramUniform4ui");
		glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)glfGetProcAddress("glProgramUniform4uiv");

		glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)glfGetProcAddress("glProgramUniform1f");
		glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)glfGetProcAddress("glProgramUniform1fv");
		glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)glfGetProcAddress("glProgramUniform2f");
		glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)glfGetProcAddress("glProgramUniform2fv");
		glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)glfGetProcAddress("glProgramUniform3f");
		glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)glfGetProcAddress("glProgramUniform3fv");
		glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)glfGetProcAddress("glProgramUniform4f");
		glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)glfGetProcAddress("glProgramUniform4fv");

		glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)glfGetProcAddress("glProgramUniform1d");
		glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)glfGetProcAddress("glProgramUniform2d");
		glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)glfGetProcAddress("glProgramUniform3d");
		glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)glfGetProcAddress("glProgramUniform4d");
		glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)glfGetProcAddress("glProgramUniform1dv");
		glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)glfGetProcAddress("glProgramUniform2dv");
		glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)glfGetProcAddress("glProgramUniform3dv");
		glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)glfGetProcAddress("glProgramUniform4dv");

		glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)glfGetProcAddress("glProgramUniformMatrix2fv");
		glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)glfGetProcAddress("glProgramUniformMatrix3fv");
		glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)glfGetProcAddress("glProgramUniformMatrix4fv");
		glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)glfGetProcAddress("glProgramUniformMatrix2x3fv");
		glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)glfGetProcAddress("glProgramUniformMatrix2x4fv");
		glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)glfGetProcAddress("glProgramUniformMatrix3x2fv");
		glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)glfGetProcAddress("glProgramUniformMatrix3x4fv");
		glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)glfGetProcAddress("glProgramUniformMatrix4x2fv");
		glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)glfGetProcAddress("glProgramUniformMatrix4x3fv");

		glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)glfGetProcAddress("glProgramUniformMatrix2dv");
		glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)glfGetProcAddress("glProgramUniformMatrix3dv");
		glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)glfGetProcAddress("glProgramUniformMatrix4dv");
		glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)glfGetProcAddress("glProgramUniformMatrix2x3dv");
		glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)glfGetProcAddress("glProgramUniformMatrix2x4dv");
		glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)glfGetProcAddress("glProgramUniformMatrix3x2dv");
		glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)glfGetProcAddress("glProgramUniformMatrix3x4dv");
		glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)glfGetProcAddress("glProgramUniformMatrix4x2dv");
		glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)glfGetProcAddress("glProgramUniformMatrix4x3dv");

		glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)glfGetProcAddress("glUseProgramStages");
		glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)glfGetProcAddress("glActiveShaderProgram");
		glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)glfGetProcAddress("glCreateShaderProgramv");
		glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)glfGetProcAddress("glBindProgramPipeline");
		glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)glfGetProcAddress("glDeleteProgramPipelines");
		glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)glfGetProcAddress("glGenProgramPipelines");
		glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)glfGetProcAddress("glIsProgramPipeline");
		glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)glfGetProcAddress("glProgramParameteri");
		glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)glfGetProcAddress("glGetProgramPipelineiv");
		glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)glfGetProcAddress("glValidateProgramPipeline");
		glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)glfGetProcAddress("glGetProgramPipelineInfoLog");

		glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)glfGetProcAddress("glViewportArrayv");;
		glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)glfGetProcAddress("glViewportIndexedf");
		glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)glfGetProcAddress("glViewportIndexedfv");
		glScissorArrayv = (PFNGLSCISSORARRAYVPROC)glfGetProcAddress("glScissorArrayv");
		glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)glfGetProcAddress("glScissorIndexed");
		glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)glfGetProcAddress("glScissorIndexedv");
		glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)glfGetProcAddress("glDepthRangeArrayv");
		glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)glfGetProcAddress("glDepthRangeIndexed");
		glGetFloati_v = (PFNGLGETFLOATI_VPROC)glfGetProcAddress("glGetFloati_v");
		glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)glfGetProcAddress("glGetDoublei_v");

		glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)glfGetProcAddress("glGetProgramBinary");
		glProgramBinary = (PFNGLPROGRAMBINARYPROC)glfGetProcAddress("glProgramBinary");

		// Load GL_ARB_debug_output
		glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC) glfGetProcAddress("glDebugMessageControlARB");
		glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC) glfGetProcAddress("glDebugMessageInsertARB");
		glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC) glfGetProcAddress("glDebugMessageCallbackARB");
		glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC) glfGetProcAddress("glGetDebugMessageLogARB");

#endif//WIN32
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

	bool checkFramebuffer(GLuint FramebufferName)
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

	static void debugOutput
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
			 char debSource[16], debType[20], debSev[5];
			 if(source == 0x8246)
					strcpy(debSource, "OpenGL");
			 else if(source == 0x8247)
					strcpy(debSource, "Windows");
			 else if(source == 0x8248)
					strcpy(debSource, "Shader Compiler");
			 else if(source == 0x8249)
					strcpy(debSource, "Third Party");
			 else if(source == 0x824A)
					strcpy(debSource, "Application");
			 else if(source == 0x824B)
					strcpy(debSource, "Other");

			 if(type == 0x824C)
					strcpy(debType, "Error");
			 else if(type == 0x824D)
					strcpy(debType, "Deprecated behavior");
			 else if(type == 0x824E)
					strcpy(debType, "Undefined behavior");
			 else if(type == 0x824F)
					strcpy(debType, "Portability");
			 else if(type == 0x8250)
					strcpy(debType, "Performance");
			 else if(type == 0x8251)
					strcpy(debType, "Other");

			 if(severity == 0x9146)
					strcpy(debSev, "High");
			 else if(severity == 0x9147)
					strcpy(debSev, "Medium");
			 else if(severity == 0x9148)
					strcpy(debSev, "Low");

			 fprintf(stderr,"Source:%s\tType:%s\tID:%d\tSeverity:%s\tMessage:%s\n", debSource,debType,id,debSev,message);
			 //fclose(f);
		}
	}

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

	inline int version(int Major, int Minor)
	{
		return Major * 100 + Minor * 10;
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		switch(key) 
		{
		case 27:
			end();
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

	static void close()
	{
		end();
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
		if(glf::version(Major, Minor) >= 320)
		{
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
			glutInitContextProfile(GLUT_CORE_PROFILE);
		}

		glutCreateWindow(argv[0]);
		glewInit();
		glGetError();
		glf::init();

		if(begin())
		{
			glutDisplayFunc(display); 
			glutReshapeFunc(glf::reshape);
			glutMouseFunc(glf::mouse);
			glutMotionFunc(glf::motion);
			glutKeyboardFunc(glf::keyboard);
			glutIdleFunc(glf::idle);
			glutCloseFunc(glf::close);

			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

			glutMainLoop();

			return 0;
		}

		return 1;
	}

}//namespace glf
