//#define GL3_PROTOTYPES
//#include <GL/gl3.h>
//#define __gl_h_
#define _CRT_SECURE_NO_WARNINGS

#include "GL/glew.h"

#include "GL/freeglut.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_projection.hpp" // glm::perspective
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/gtx/transform2.hpp" // lookAt
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "glf/glf.hpp"

GLsizei const RendererElementCount = 3;
GLsizeiptr const RendererElementSize = RendererElementCount * sizeof(glm::uint32);
glm::uint32 const RendererElementData[RendererElementCount] =
{
	0, 1, 2,
	//0, 2, 3
};

GLsizei const RendererVertexCount = 3;
GLsizeiptr const RendererPositionSize = RendererVertexCount * sizeof(glm::vec4);
glm::vec4 const RendererPositionData[RendererVertexCount] =
{
	glm::vec4( 1.0f, 0.0f,0,1),
	glm::vec4( 0.0f, 1.0f,0,1),
	glm::vec4( 0.0f, 0.0f,0,1),
	//glm::vec4(-1.0f, 1.0f,0,0)
};

GLsizei const TonemapperElementCount = 3;
GLsizeiptr const TonemapperElementSize = TonemapperElementCount * sizeof(glm::uint32);
glm::uint32 const TonemapperElementData[TonemapperElementCount] =
{
	0, 1, 2,
};

GLsizei const TonemapperVertexCount = 3;
GLsizeiptr const TonemapperPositionSize = TonemapperVertexCount * sizeof(glm::vec4);
glm::vec4 const TonemapperPositionData[TonemapperVertexCount] =
{ // A full-screen triangle in normalized screen space.
	glm::vec4( -1.0f, -1.0f,0,1),
	glm::vec4( 3.0f, -1.0f,0,1),
	glm::vec4( -1.0f, 3.0f,0,1),
};


// The VAO. Unique for the whole openGL context.
GLuint VertexArrayName = 0;

// The renderer's VBO
GLuint RendererArrayBufferName = 0;   // The Position buffer
GLuint RendererElementBufferName = 0; // The Index buffer

// The renderer's shader
GLuint RendererProgramName = 0;       // The program's ID
GLuint RendererPositionLocation = 0;  // Location of the Position buffer as seen from the shader
GLuint RendererUniformMVP = 0;        // Location of the MVP matrix

// The renderer's framebuffer
GLuint RendererFramebufferName = 0;
GLuint RendererTexture2DName = 0;

// The renderer's VBO
GLuint TonemapperArrayBufferName = 0;   // The Position buffer
GLuint TonemapperElementBufferName = 0; // The Index buffer

// The renderer's shader
GLuint TonemapperProgramName = 0;       // The program's ID
GLuint TonemapperPositionLocation = 0;  // Location of the Position buffer as seen from the shader
GLuint TonemapperUniformRender = 0;        // Location of the sampler2D to tonemap

// The renderer's framebuffer
GLuint TonemapperFramebufferName = 0;
GLuint TonemapperTexture2DName = 0;



bool initRendererProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		GLuint RendererVertexShaderName = glf::createShader(GL_VERTEX_SHADER, "../data/shaders/basic.vs");
		GLuint RendererFragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, "../data/shaders/basic.fs");

		RendererProgramName = glCreateProgram();
		glAttachShader(RendererProgramName, RendererVertexShaderName);
		glAttachShader(RendererProgramName, RendererFragmentShaderName);
		glDeleteShader(RendererVertexShaderName);
		glDeleteShader(RendererFragmentShaderName);

		glLinkProgram(RendererProgramName);
		RendererPositionLocation = glGetAttribLocation (RendererProgramName, "Position") ;

		Validated = glf::checkProgram(RendererProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		RendererUniformMVP = glGetUniformLocation(RendererProgramName, "MVP");
	}

	return Validated && glf::checkError("initProgram");
}

bool initTonemapperProgram()
{
	bool Validated = true;
	
	// Create program
	if(Validated)
	{
		GLuint TonemapperVertexShaderName = glf::createShader(GL_VERTEX_SHADER, "../data/shaders/tonemapping.vs");
		GLuint TonemapperFragmentShaderName = glf::createShader(GL_FRAGMENT_SHADER, "../data/shaders/tonemapping.fs");

		TonemapperProgramName = glCreateProgram();
		glAttachShader(TonemapperProgramName, TonemapperVertexShaderName);
		glAttachShader(TonemapperProgramName, TonemapperFragmentShaderName);
		glDeleteShader(TonemapperVertexShaderName);
		glDeleteShader(TonemapperFragmentShaderName);

		glLinkProgram(TonemapperProgramName);
		RendererPositionLocation = glGetAttribLocation (TonemapperProgramName, "Position") ;

		Validated = glf::checkProgram(TonemapperProgramName);
	}

	// Get variables locations
	if(Validated)
	{
		TonemapperUniformRender = glGetUniformLocation(TonemapperProgramName, "t_MS_HDR");
	}

	return Validated && glf::checkError("initProgram");
}

bool initVertexArrayObject(){
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);

	return glf::checkError("vao init");
}

bool initRendererArrayBuffer()
{
	glGenBuffers(1, &RendererArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, RendererArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, RendererPositionSize, RendererPositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &RendererElementBufferName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererElementBufferName);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, RendererElementSize, RendererElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, RendererArrayBufferName);
	glVertexAttribPointer(RendererPositionLocation, 4, GL_FLOAT, GL_FALSE,0,0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(RendererPositionLocation);

	return glf::checkError("buffers init");
}

bool initTonemapperArrayBuffer()
{
	glGenBuffers(1, &TonemapperArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, TonemapperArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, TonemapperPositionSize, TonemapperPositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &TonemapperElementBufferName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TonemapperElementBufferName);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, TonemapperElementSize, TonemapperElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, TonemapperArrayBufferName);
	glVertexAttribPointer(TonemapperPositionLocation, 4, GL_FLOAT, GL_FALSE,0,0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(TonemapperPositionLocation);

	return glf::checkError("buffers init");
}



bool initRendererTexture2D()
{
	glGenTextures(1, &RendererTexture2DName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, RendererTexture2DName);


	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, 1024, 1024, GL_FALSE);

	return glf::checkError("initTexture2D");
}



bool initRendererFramebuffer()
{
	glGenFramebuffers(1, &RendererFramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, RendererFramebufferName);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, RendererTexture2DName, 0);
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return glf::checkError("initFramebuffer");
}



void Draw(){ 	

	// RTT
	glBindFramebuffer(GL_FRAMEBUFFER, RendererFramebufferName);

	glViewport(0, 0, 1024,1024);
	//glClearColor(1,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glm::mat4 Projection = glm::perspective(60.0f, 4.0f / 4.0f, 0.1f, 100.f);
	glm::mat4 View = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 Model; 
	glm::mat4 MVP = Projection * View * Model;
	glEnable(GL_MULTISAMPLE);

	glUseProgram(RendererProgramName);

		glUniformMatrix4fv(RendererUniformMVP, 1,false, &MVP[0][0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererElementBufferName);
		glDrawElements(GL_TRIANGLES, RendererElementCount, GL_UNSIGNED_INT,0);

	glDisable(GL_MULTISAMPLE);

	// render to screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, 1024,1024);
	glClearColor(0,0,0.3f,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(TonemapperProgramName);
		glUniform1i(TonemapperUniformRender, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, RendererTexture2DName);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TonemapperElementBufferName);
		glDrawElements(GL_TRIANGLES, TonemapperElementCount, GL_UNSIGNED_INT,0);

	
	
	glf::checkError("Draw");
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int nargs, char *vargs[]){
    glutInitContextVersion (4, 0);
    glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInit(&nargs, vargs);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1024,1024); 
	glutCreateWindow("PBRasterizer");
	glutDisplayFunc(Draw);
	glf::checkError("glut init");

	glewInit();
	glf::checkError("glew init");

	initRendererProgram();
	initTonemapperProgram();

	initVertexArrayObject();

	initRendererArrayBuffer();
	initTonemapperArrayBuffer();

	initRendererTexture2D();

	initRendererFramebuffer();

	glutMainLoop();


	//glDeleteBuffers(1, &RendererArrayBufferName);
	////glDeleteBuffers(1, &ElementBufferName);
	//glDeleteProgram(ProgramName);

	return 0;
}


