#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

bool check();
bool begin();
bool end();
void display();

#ifdef _WIN32
#define GLF_APIENTRY __stdcall
#else 
#define GLF_APIENTRY GLAPIENTRY
#endif

typedef void (GLF_APIENTRY * PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void* indirect, GLsizei primcount, GLsizei stride);
typedef void (GLF_APIENTRY * PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const GLvoid* indirect, GLsizei primcount, GLsizei stride);

PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirectAMD = 0;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirectAMD = 0;

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
#if ((defined(WIN32) || defined(__GNUC__) || defined(__MINGW32__)) && !defined(__APPLE__))
		glewInit();
		glGetError();

		// Load OpenGL 3.0 functions
		glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)glutGetProcAddress("glBindBufferBase");
		glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)glutGetProcAddress("glBindFragDataLocation");
		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glutGetProcAddress("glGenerateMipmap");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glutGetProcAddress("glDeleteVertexArrays");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glutGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glutGetProcAddress("glBindVertexArray");
		glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glutGetProcAddress("glGenFramebuffers");
		glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glutGetProcAddress("glBindFramebuffer");
		glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)glutGetProcAddress("glFramebufferTextureLayer");
		glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glutGetProcAddress("glFramebufferTexture2D");
		glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)glutGetProcAddress("glCheckFramebufferStatus");
		glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glutGetProcAddress("glDeleteFramebuffers");
		glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)glutGetProcAddress("glMapBufferRange");
		glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)glutGetProcAddress("glFlushMappedBufferRange");
		glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glutGetProcAddress("glGenRenderbuffers");
		glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glutGetProcAddress("glBindRenderbuffer");
		glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glutGetProcAddress("glRenderbufferStorage");
		glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glutGetProcAddress("glFramebufferRenderbuffer");
		glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)glutGetProcAddress("glBlitFramebuffer");
		glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glutGetProcAddress("glDeleteRenderbuffers");
		glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)glutGetProcAddress("glRenderbufferStorageMultisample");
		glColorMaski = (PFNGLCOLORMASKIPROC)glutGetProcAddress("glColorMaski");
		glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)glutGetProcAddress("glGetBooleani_v");
		glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)glutGetProcAddress("glGetIntegeri_v");
		glEnablei = (PFNGLENABLEIPROC)glutGetProcAddress("glEnablei");
		glDisablei = (PFNGLDISABLEIPROC)glutGetProcAddress("glDisablei");

		// Load OpenGL 3.1 functions
		glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)glutGetProcAddress("glBindBufferBase");
		glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)glutGetProcAddress("glBindBufferRange");
		glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)glutGetProcAddress("glDrawArraysInstanced");
		glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)glutGetProcAddress("glDrawElementsInstanced");
		glTexBuffer = (PFNGLTEXBUFFERPROC)glutGetProcAddress("glTexBuffer");
		glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)glutGetProcAddress("glPrimitiveRestartIndex");
		glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)glutGetProcAddress("glGetUniformIndices");
		glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)glutGetProcAddress("glGetActiveUniformsiv");
		glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)glutGetProcAddress("glGetActiveUniformName");
		glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)glutGetProcAddress("glGetUniformBlockIndex");
		glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)glutGetProcAddress("glGetActiveUniformBlockiv");
		glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)glutGetProcAddress("glGetActiveUniformBlockName");
		glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)glutGetProcAddress("glUniformBlockBinding");

		// Load OpenGL 3.2 functions
		glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)glutGetProcAddress("glDrawElementsBaseVertex");
		glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)glutGetProcAddress("glDrawElementsInstancedBaseVertex");
		glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)glutGetProcAddress("glDrawRangeElementsBaseVertex");
		glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)glutGetProcAddress("glMultiDrawElementsBaseVertex");
		glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)glutGetProcAddress("glTexImage2DMultisample");
		glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)glutGetProcAddress("glTexImage3DMultisample");

		// Load OpenGL 3.3 functions
		glGenSamplers = (PFNGLGENSAMPLERSPROC)glutGetProcAddress("glGenSamplers");
		glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)glutGetProcAddress("glDeleteSamplers");
		glIsSampler = (PFNGLISSAMPLERPROC)glutGetProcAddress("glIsSampler");
		glBindSampler = (PFNGLBINDSAMPLERPROC)glutGetProcAddress("glBindSampler");
		glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)glutGetProcAddress("glSamplerParameteri");
		glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)glutGetProcAddress("glSamplerParameteriv");
		glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)glutGetProcAddress("glSamplerParameterf");
		glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)glutGetProcAddress("glSamplerParameterfv");
		glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)glutGetProcAddress("glSamplerParameterIiv");
		glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)glutGetProcAddress("glSamplerParameterIuiv");
		glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)glutGetProcAddress("glGetSamplerParameteriv");
		glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)glutGetProcAddress("glGetSamplerParameterIiv");
		glGetSamplerParameterfv =   (PFNGLGETSAMPLERPARAMETERFVPROC)glutGetProcAddress("glGetSamplerParameterfv");
		glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)glutGetProcAddress("glGetSamplerParameterIuiv");
		glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORARBPROC)glutGetProcAddress("glVertexAttribDivisor");

		// Load OpenGL 4.0 functions
		glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)glutGetProcAddress("glBindTransformFeedback");
		glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)glutGetProcAddress("glDeleteTransformFeedbacks");
		glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)glutGetProcAddress("glGenTransformFeedbacks");
		glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)glutGetProcAddress("glIsTransformFeedback");
		glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)glutGetProcAddress("glPauseTransformFeedback");
		glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)glutGetProcAddress("glResumeTransformFeedback");
		glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)glutGetProcAddress("glDrawTransformFeedback");
		glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)glutGetProcAddress("glPatchParameteri");
		glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)glutGetProcAddress("glPatchParameterfv");
		glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)glutGetProcAddress("glGetActiveSubroutineName");
		glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)glutGetProcAddress("glGetActiveSubroutineUniformName");
		glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)glutGetProcAddress("glGetActiveSubroutineUniformiv");
		glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)glutGetProcAddress("glGetProgramStageiv");
		glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)glutGetProcAddress("glGetSubroutineIndex");
		glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)glutGetProcAddress("glGetSubroutineUniformLocation");
		glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)glutGetProcAddress("glGetUniformSubroutineuiv");
		glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)glutGetProcAddress("glUniformSubroutinesuiv");
		glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)glutGetProcAddress("glDrawArraysIndirect");
		glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)glutGetProcAddress("glDrawElementsIndirect");
		glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)glutGetProcAddress("glBlendEquationSeparatei");
		glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)glutGetProcAddress("glBlendEquationi");
		glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)glutGetProcAddress("glBlendFuncSeparatei");
		glBlendFunci = (PFNGLBLENDFUNCIPROC)glutGetProcAddress("glBlendFunci");
		glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)glutGetProcAddress("glMinSampleShading");
		glSampleMaski = (PFNGLSAMPLEMASKIPROC)glutGetProcAddress("glSampleMaski");

		glUniform1d = (PFNGLUNIFORM1DPROC)glutGetProcAddress("glUniform1d");
		glUniform2d = (PFNGLUNIFORM2DPROC)glutGetProcAddress("glUniform2d");
		glUniform3d = (PFNGLUNIFORM3DPROC)glutGetProcAddress("glUniform3d");
		glUniform4d = (PFNGLUNIFORM4DPROC)glutGetProcAddress("glUniform4d");
		glUniform1dv = (PFNGLUNIFORM1DVPROC)glutGetProcAddress("glUniform1dv");
		glUniform2dv = (PFNGLUNIFORM2DVPROC)glutGetProcAddress("glUniform2dv");
		glUniform3dv = (PFNGLUNIFORM3DVPROC)glutGetProcAddress("glUniform3dv");
		glUniform4dv = (PFNGLUNIFORM4DVPROC)glutGetProcAddress("glUniform4dv");
		glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)glutGetProcAddress("glUniformMatrix2dv");
		glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)glutGetProcAddress("glUniformMatrix3dv");
		glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)glutGetProcAddress("glUniformMatrix4dv");
		glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)glutGetProcAddress("glUniformMatrix2x3dv");
		glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)glutGetProcAddress("glUniformMatrix2x4dv");
		glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)glutGetProcAddress("glUniformMatrix3x2dv");
		glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)glutGetProcAddress("glUniformMatrix3x4dv");
		glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)glutGetProcAddress("glUniformMatrix4x2dv");
		glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)glutGetProcAddress("glUniformMatrix4x3dv");

		// Load OpenGL 4.1 functions
		glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)glutGetProcAddress("glVertexAttribLPointer");

		glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)glutGetProcAddress("glProgramUniform1i");
		glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)glutGetProcAddress("glProgramUniform1iv");
		glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)glutGetProcAddress("glProgramUniform2i");
		glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)glutGetProcAddress("glProgramUniform2iv");
		glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)glutGetProcAddress("glProgramUniform3i");
		glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)glutGetProcAddress("glProgramUniform3iv");
		glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)glutGetProcAddress("glProgramUniform4i");
		glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)glutGetProcAddress("glProgramUniform4iv");

		glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)glutGetProcAddress("glProgramUniform1ui");
		glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)glutGetProcAddress("glProgramUniform1uiv");
		glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)glutGetProcAddress("glProgramUniform2ui");
		glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)glutGetProcAddress("glProgramUniform2uiv");
		glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)glutGetProcAddress("glProgramUniform3ui");
		glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)glutGetProcAddress("glProgramUniform3uiv");
		glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)glutGetProcAddress("glProgramUniform4ui");
		glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)glutGetProcAddress("glProgramUniform4uiv");

		glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)glutGetProcAddress("glProgramUniform1f");
		glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)glutGetProcAddress("glProgramUniform1fv");
		glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)glutGetProcAddress("glProgramUniform2f");
		glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)glutGetProcAddress("glProgramUniform2fv");
		glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)glutGetProcAddress("glProgramUniform3f");
		glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)glutGetProcAddress("glProgramUniform3fv");
		glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)glutGetProcAddress("glProgramUniform4f");
		glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)glutGetProcAddress("glProgramUniform4fv");

		glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)glutGetProcAddress("glProgramUniform1d");
		glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)glutGetProcAddress("glProgramUniform2d");
		glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)glutGetProcAddress("glProgramUniform3d");
		glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)glutGetProcAddress("glProgramUniform4d");
		glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)glutGetProcAddress("glProgramUniform1dv");
		glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)glutGetProcAddress("glProgramUniform2dv");
		glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)glutGetProcAddress("glProgramUniform3dv");
		glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)glutGetProcAddress("glProgramUniform4dv");

		glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)glutGetProcAddress("glProgramUniformMatrix2fv");
		glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)glutGetProcAddress("glProgramUniformMatrix3fv");
		glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)glutGetProcAddress("glProgramUniformMatrix4fv");
		glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)glutGetProcAddress("glProgramUniformMatrix2x3fv");
		glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)glutGetProcAddress("glProgramUniformMatrix2x4fv");
		glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)glutGetProcAddress("glProgramUniformMatrix3x2fv");
		glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)glutGetProcAddress("glProgramUniformMatrix3x4fv");
		glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)glutGetProcAddress("glProgramUniformMatrix4x2fv");
		glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)glutGetProcAddress("glProgramUniformMatrix4x3fv");

		glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)glutGetProcAddress("glProgramUniformMatrix2dv");
		glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)glutGetProcAddress("glProgramUniformMatrix3dv");
		glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)glutGetProcAddress("glProgramUniformMatrix4dv");
		glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)glutGetProcAddress("glProgramUniformMatrix2x3dv");
		glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)glutGetProcAddress("glProgramUniformMatrix2x4dv");
		glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)glutGetProcAddress("glProgramUniformMatrix3x2dv");
		glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)glutGetProcAddress("glProgramUniformMatrix3x4dv");
		glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)glutGetProcAddress("glProgramUniformMatrix4x2dv");
		glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)glutGetProcAddress("glProgramUniformMatrix4x3dv");

		glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)glutGetProcAddress("glUseProgramStages");
		glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)glutGetProcAddress("glActiveShaderProgram");
		glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)glutGetProcAddress("glCreateShaderProgramv");
		glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)glutGetProcAddress("glBindProgramPipeline");
		glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)glutGetProcAddress("glDeleteProgramPipelines");
		glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)glutGetProcAddress("glGenProgramPipelines");
		glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)glutGetProcAddress("glIsProgramPipeline");
		glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)glutGetProcAddress("glProgramParameteri");
		glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)glutGetProcAddress("glGetProgramPipelineiv");
		glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)glutGetProcAddress("glValidateProgramPipeline");
		glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)glutGetProcAddress("glGetProgramPipelineInfoLog");

		glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)glutGetProcAddress("glViewportArrayv");;
		glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)glutGetProcAddress("glViewportIndexedf");
		glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)glutGetProcAddress("glViewportIndexedfv");
		glScissorArrayv = (PFNGLSCISSORARRAYVPROC)glutGetProcAddress("glScissorArrayv");
		glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)glutGetProcAddress("glScissorIndexed");
		glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)glutGetProcAddress("glScissorIndexedv");
		glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)glutGetProcAddress("glDepthRangeArrayv");
		glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)glutGetProcAddress("glDepthRangeIndexed");
		glGetFloati_v = (PFNGLGETFLOATI_VPROC)glutGetProcAddress("glGetFloati_v");
		glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)glutGetProcAddress("glGetDoublei_v");

		glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)glutGetProcAddress("glGetProgramBinary");
		glProgramBinary = (PFNGLPROGRAMBINARYPROC)glutGetProcAddress("glProgramBinary");

		// Load GL_ARB_debug_output
		glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC) glutGetProcAddress("glDebugMessageControlARB");
		glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC) glutGetProcAddress("glDebugMessageInsertARB");
		glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC) glutGetProcAddress("glDebugMessageCallbackARB");
		glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC) glutGetProcAddress("glGetDebugMessageLogARB");

		// Load GL_EXT_direct_state_access extension
		glNamedBufferDataEXT = (PFNGLNAMEDBUFFERDATAEXTPROC)glutGetProcAddress("glNamedBufferDataEXT");
		glTextureImage2DEXT = (PFNGLTEXTUREIMAGE2DEXTPROC)glutGetProcAddress("glTextureImage2DEXT");
		glTextureParameteriEXT = (PFNGLTEXTUREPARAMETERIEXTPROC)glutGetProcAddress("glTextureParameteriEXT");
		glGenerateTextureMipmapEXT = (PFNGLGENERATETEXTUREMIPMAPEXTPROC)glutGetProcAddress("glGenerateTextureMipmapEXT");
		glCompressedTextureImage2DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)glutGetProcAddress("glCompressedTextureImage2DEXT");
		glVertexArrayVertexAttribOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC)glutGetProcAddress("glVertexArrayVertexAttribOffsetEXT");
		glEnableVertexArrayAttribEXT = (PFNGLENABLEVERTEXARRAYATTRIBEXTPROC)glutGetProcAddress("glEnableVertexArrayAttribEXT");
		glBindMultiTextureEXT = (PFNGLBINDMULTITEXTUREEXTPROC)glutGetProcAddress("glBindMultiTextureEXT");
		glProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)glutGetProcAddress("glProgramUniformMatrix4fvEXT");
		glProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC)glutGetProcAddress("glProgramUniform1iEXT");
		glProgramUniform1dEXT = (PFNGLPROGRAMUNIFORM1DEXTPROC)glutGetProcAddress("glProgramUniform1dEXT");
		glProgramUniform2dEXT = (PFNGLPROGRAMUNIFORM2DEXTPROC)glutGetProcAddress("glProgramUniform2dEXT");
		glProgramUniform3dEXT = (PFNGLPROGRAMUNIFORM3DEXTPROC)glutGetProcAddress("glProgramUniform3dEXT");
		glProgramUniform4dEXT = (PFNGLPROGRAMUNIFORM4DEXTPROC)glutGetProcAddress("glProgramUniform4dEXT");
		glProgramUniform1dvEXT = (PFNGLPROGRAMUNIFORM1DVEXTPROC)glutGetProcAddress("glProgramUniform1dvEXT");
		glProgramUniform2dvEXT = (PFNGLPROGRAMUNIFORM2DVEXTPROC)glutGetProcAddress("glProgramUniform2dvEXT");
		glProgramUniform3dvEXT = (PFNGLPROGRAMUNIFORM3DVEXTPROC)glutGetProcAddress("glProgramUniform3dvEXT");
		glProgramUniform4dvEXT = (PFNGLPROGRAMUNIFORM4DVEXTPROC)glutGetProcAddress("glProgramUniform4dvEXT");
		glProgramUniformMatrix2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix2dvEXT");
		glProgramUniformMatrix3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix3dvEXT");
		glProgramUniformMatrix4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix4dvEXT");
		glProgramUniformMatrix2x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix2x3dvEXT");
		glProgramUniformMatrix2x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix2x4dvEXT");
		glProgramUniformMatrix3x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix3x2dvEXT");
		glProgramUniformMatrix3x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix3x4dvEXT");
		glProgramUniformMatrix4x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix4x2dvEXT");
		glProgramUniformMatrix4x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)glutGetProcAddress("glProgramUniformMatrix4x3dvEXT");
		glVertexArrayVertexAttribLOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)glutGetProcAddress("glVertexArrayVertexAttribLOffsetEXT");
		glEnableVertexArrayAttribEXT = (PFNGLENABLEVERTEXARRAYATTRIBEXTPROC)glutGetProcAddress("glEnableVertexArrayAttribEXT");
		glNamedRenderbufferStorageMultisampleEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)glutGetProcAddress("glNamedRenderbufferStorageMultisampleEXT"); 
		glNamedFramebufferRenderbufferEXT = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)glutGetProcAddress("glNamedFramebufferRenderbufferEXT"); 
		glNamedFramebufferTextureEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)glutGetProcAddress("glNamedFramebufferTextureEXT"); 
		glCheckNamedFramebufferStatusEXT = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)glutGetProcAddress("glCheckNamedFramebufferStatusEXT"); 
		glFramebufferDrawBuffersEXT = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)glutGetProcAddress("glFramebufferDrawBuffersEXT");

		// Load GL_EXT_shader_image_load_store extension
		glBindImageTextureEXT = (PFNGLBINDIMAGETEXTUREEXTPROC)glutGetProcAddress("glBindImageTextureEXT");

		glGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC)glutGetProcAddress("glGetBufferParameterui64vNV");
		glMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC)glutGetProcAddress("glMakeBufferResidentNV");
		glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)glutGetProcAddress("glVertexAttribFormatNV");
		glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)glutGetProcAddress("glBufferAddressRangeNV");

		// Load GL_AMD_multi_draw_indirect extension
		glMultiDrawArraysIndirectAMD = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)glutGetProcAddress("glMultiDrawArraysIndirectAMD");
		glMultiDrawElementsIndirectAMD = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)glutGetProcAddress("glMultiDrawElementsIndirectAMD");

		// Load GL_NV_copy_image extension
		glCopyImageSubDataNV = (PFNGLCOPYIMAGESUBDATANVPROC)glutGetProcAddress("glCopyImageSubDataNV");
#endif// All but Apple
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
	static void APIENTRY debugOutput
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
#endif
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
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);// | GLUT_MULTISAMPLE);
#if !defined(__APPLE__)
		glutInitContextVersion(Major, Minor);
		if(glf::version(Major, Minor) >= 320)
		{
			glutInitContextProfile(GLUT_CORE_PROFILE); // GLUT_COMPATIBILITY_PROFILE
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
		}
#endif//__APPLE__

		glutCreateWindow(argv[0]);

#if !defined(__APPLE__)
		glewInit();
#endif//__APPLE__

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
