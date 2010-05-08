#ifndef GLF_WINDOW_INCLUDED
#define GLF_WINDOW_INCLUDED

// OpenGL
#ifdef WIN32
#	define GLEW_STATIC
#	include <GL/glew.h>
#	include <GL/wglew.h>
#	include <GL/glext.h>
#	define glfGetProcAddress wglGetProcAddress
#elif defined(linux) || defined(__linux)
#	define GL_GLEXT_PROTOTYPES 1
#	include <GL/gl.h>
#	include <GL/glext.h>
#elif defined(__APPLE__)
#	include <OpenGL/gl.h>
#else
#	error "System unsuported..."
#endif

// GLF libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/half_float.hpp>
#include <glm/gtc/type_precision.hpp>

#include <gli/gli.hpp>

// STL
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

namespace glf
{
	static GLint const SAMPLE_MAJOR = 3;
	static GLint const SAMPLE_MINOR = 3;
	static std::string const DATA_DIRECTORY("../../data/");

	enum mouse_button
	{
		MOUSE_BUTTON_NONE = 0,
		MOUSE_BUTTON_LEFT = (1 << 0),
		MOUSE_BUTTON_RIGHT = (1 << 1),
		MOUSE_BUTTON_MIDDLE = (1 << 2)
	};

	class window
	{
	public:
		window(
			std::string const & Title, 
			glm::ivec2 const & WindowSise);
		window(
			std::string const & Title, 
			glm::ivec2 const & WindowSise,
			glm::uint32 VersionMajor,
			glm::uint32 VersionMinor);
		virtual ~window();

		virtual bool check() const = 0;
		virtual bool begin(glm::ivec2 const & WindowSize) = 0;
		virtual bool end() = 0;
		virtual void render() = 0;

		bool run();
		void onMouseMove(glm::vec2 const & MouseCurrent);
		void onMouseDown(mouse_button MouseButton);
		void onMouseUp(mouse_button MouseButton);

		std::string title(){return Title;}

	protected:
		glm::uint MouseButtonFlags;
		glm::vec2 RotationOrigin;
		glm::vec2 RotationCurrent;
		glm::vec2 TranlationOrigin;
		glm::vec2 TranlationCurrent;
		glm::vec2 MouseCurrent;
		glm::vec2 MouseOrigin;
		int IndexCurrent;
		int IndexMax;
		glm::ivec2 WindowSize;

	private:
		std::string Title;
	};

	std::string loadFile(std::string const & Filename);
	bool checkError(const char* Title);
	bool checkProgram(GLuint ProgramName);
	bool checkShader(GLuint ShaderName, char const* Source);
	bool validateProgram(GLuint ProgramName);

	GLuint createProgram(
		std::string const & VertShader, 
		std::string const & FragShader);

	int run();

	namespace semantic
	{
		namespace uniform
		{
			enum type
			{
				TRANSFORM = 0,
				MATERIAL  = 1
			};
		};

		namespace attr
		{
			enum type
			{
				POSITION = 0,
				COLOR	 = 3,
				TEXCOORD = 4
			};
		}//namespace attr

		namespace vert
		{
			enum type
			{
				POSITION = 0,
				COLOR	 = 3,
				TEXCOORD = 4,
				INSTANCE = 7
			};
		}//namespace vert

		namespace frag
		{
			enum type
			{
				COLOR	= 0,
				RED		= 0,
				GREEN	= 1,
				BLUE	= 2,
				ALPHA	= 0
			};
		}//namespace frag

	}//namespace semantic

}//namespace glf

#define GLF_BUFFER_OFFSET(i) ((char *)NULL + (i))

#include "window.inl"

#endif//GLF_WINDOW_INCLUDED
