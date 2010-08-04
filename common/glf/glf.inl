#include <GL/freeglut.h>

#ifdef WIN32
#	ifndef APIENTRY
#		define APIENTRY
#	endif
#	ifndef APIENTRYP
#		define APIENTRYP APIENTRY *
#	endif

// Declare OpenGL 4.1 enums
#define GL_VERTEX_SHADER_BIT                      0x00000001
#define GL_FRAGMENT_SHADER_BIT                    0x00000002
#define GL_GEOMETRY_SHADER_BIT                    0x00000004
#define GL_TESS_CONTROL_SHADER_BIT                0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT             0x00000010
#define GL_ALL_SHADER_BITS                        0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE                      0x8258
#define GL_ACTIVE_PROGRAM                         0x8259
#define GL_PROGRAM_PIPELINE_BINDING               0x825A

// Declare OpenGL 4.1 functions
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
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

typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
typedef void (GLAPIENTRY * PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);

typedef void (GLAPIENTRY * PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (GLAPIENTRY * PFNGLACTIVESHADERPROGRAM) (GLuint pipeline, GLuint program);
typedef GLuint (GLAPIENTRY * PFNGLCREATESHADERPROGRAMV) (GLenum type, GLsizei count, const GLchar **strings);
typedef void (GLAPIENTRY * PFNGLBINDPROGRAMPIPELINE) (GLuint pipeline);
typedef void (GLAPIENTRY * PFNGLDELETEPROGRAMPIPELINES) (GLsizei n, const GLuint *pipelines);
typedef void (GLAPIENTRY * PFNGLGENPROGRAMPIPELINES) (GLsizei n, GLuint *pipelines);
typedef GLboolean (GLAPIENTRY * PFNGLISPROGRAMPIPELINE) (GLuint pipeline);
typedef void (GLAPIENTRY * PFNGLPROGRAMPARAMETERI) (GLuint program, GLenum pname, GLint value);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMPIPELINEIV) (GLuint pipeline, GLenum pname, GLint *params);
typedef void (GLAPIENTRY * PFNGLVALIDATEPROGRAMPIPELINE) (GLuint pipeline);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMPIPELINEINFOLOG) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

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
		glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAM)glfGetProcAddress("glActiveShaderProgram");
		glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMV)glfGetProcAddress("glCreateShaderProgramv");
		glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINE)glfGetProcAddress("glBindProgramPipeline");
		glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINES)glfGetProcAddress("glDeleteProgramPipelines");
		glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINES)glfGetProcAddress("glGenProgramPipelines");
		glIsProgramPipeline = (PFNGLISPROGRAMPIPELINE)glfGetProcAddress("glIsProgramPipeline");
		glProgramParameteri = (PFNGLPROGRAMPARAMETERI)glfGetProcAddress("glProgramParameteri");
		glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIV)glfGetProcAddress("glGetProgramPipelineiv");
		glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINE)glfGetProcAddress("glValidateProgramPipeline");
		glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOG)glfGetProcAddress("glGetProgramPipelineInfoLog");

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
		if(glf::version(Major, Minor) >= 300)
		{
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
			glutInitContextProfile(GLUT_CORE_PROFILE);
		}

		glutCreateWindow(argv[0]);
		glewInit();
#ifdef WIN32
		glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORARBPROC)glfGetProcAddress("glVertexAttribDivisor");
#endif//WIN32
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
