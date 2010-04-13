#ifndef GLF_SAMPLE_INCLUDED
#define GLF_SAMPLE_INCLUDED

#include <glf/window.hpp>

namespace viewport
{
	enum type
	{
		V00,
		V10,
		V11,
		V01,
		MAX
	};
}

class sample : public glf::window
{
public:
	sample(
		std::string const & Name, 
		glm::ivec2 const & WindowSize,
		glm::uint32 VersionMajor,
		glm::uint32 VersionMinor);
	virtual ~sample();

	virtual bool check() const;
    virtual bool begin(const glm::ivec2& WindowSize);
    virtual bool end();
    virtual void render();

private:
	bool initProgram();
	bool initArrayBuffer();
	bool initTexture2D();
	bool initVertexArray();

	GLuint VertexArrayName;
	GLuint ProgramName;

	GLuint BufferName;
	GLuint Texture2DName;

	GLuint UniformMVP;
	GLuint UniformDiffuse;

	GLenum SwizzleR[viewport::MAX];
	GLenum SwizzleG[viewport::MAX];
	GLenum SwizzleB[viewport::MAX];
	GLenum SwizzleA[viewport::MAX];
	glm::ivec4 Viewport[viewport::MAX];
};

#endif//GLF_SAMPLE_INCLUDED
