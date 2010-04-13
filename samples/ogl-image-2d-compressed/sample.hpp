#ifndef GLF_SAMPLE_INCLUDED
#define GLF_SAMPLE_INCLUDED

#include <glf/window.hpp>

enum texture_type
{
	TEXTURE_RGB8,
	TEXTURE_COMP,
	TEXTURE_DXT1,
	TEXTURE_DXT5,
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
	GLuint Texture2DName[TEXTURE_MAX];

	GLuint UniformMVP;
	GLuint UniformDiffuse;

	glm::ivec4 Viewport[TEXTURE_MAX];
};

#endif//GLF_SAMPLE_INCLUDED
