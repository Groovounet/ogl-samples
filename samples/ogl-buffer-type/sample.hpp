#ifndef GLF_SAMPLE_INCLUDED
#define GLF_SAMPLE_INCLUDED

#include <glf/window.hpp>

enum buffer_index
{
	BUFFER_F16,
	BUFFER_F32,
	BUFFER_I8,
	BUFFER_I32,
	BUFFER_COUNT
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
	bool initVertexArray();

	GLuint VertexArrayName;
	GLuint ProgramName;
	GLuint BufferName[BUFFER_COUNT];
	GLint UniformMVP;
	GLint UniformDiffuse;

	glm::ivec4 Viewport[BUFFER_COUNT];
	GLenum BufferType[BUFFER_COUNT];
};

#endif//GLF_SAMPLE_INCLUDED
