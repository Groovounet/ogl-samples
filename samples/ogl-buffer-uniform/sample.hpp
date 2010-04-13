#ifndef GLF_SAMPLE_INCLUDED
#define GLF_SAMPLE_INCLUDED

#include <glf/window.hpp>

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
	bool initVertexArray();
	bool initUniformBuffer();

	GLuint ProgramName;
	GLuint ElementBufferName;
	GLuint ArrayBufferName;
	GLuint VertexArrayName;
	GLuint TransformBufferName;
	GLuint MaterialBufferName;
	GLint UniformTransform;
	GLint UniformMaterial;
};

#endif//GLF_SAMPLE_INCLUDED