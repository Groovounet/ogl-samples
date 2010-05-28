#ifndef GLF_SAMPLE_INCLUDED
#define GLF_SAMPLE_INCLUDED

#include <glf/window.hpp>

enum texture_type
{
	TEXTURE_RGB8,
	TEXTURE_R,
	TEXTURE_G,
	TEXTURE_B,
	TEXTURE_MAX
};

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
    virtual bool begin(glm::ivec2 const & WindowSize);
    virtual bool end();
    virtual void render();

private:
	bool initProgram();
	bool initArrayBuffer();
	bool initTexture2D();
	bool initFramebuffer();
	bool initVertexArray();
	bool initBlend();

	GLuint FramebufferName;
	GLuint VertexArrayName;

	GLuint ProgramNameSingle;
	GLuint UniformMVPSingle;
	GLuint UniformDiffuseSingle;

	GLuint ProgramNameMultiple;
	GLuint UniformMVPMultiple;
	GLuint UniformDiffuseMultiple;

	GLuint BufferName;
	GLuint Texture2DName[TEXTURE_MAX];

	glm::ivec4 Viewport[TEXTURE_MAX];
};

#endif//GLF_SAMPLE_INCLUDED
