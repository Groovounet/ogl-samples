#ifndef GLF_SAMPLE_INCLUDED
#define GLF_SAMPLE_INCLUDED

#include <glf/window.hpp>

class sample : public glf::window
{
public:
	sample(
		std::string const & Name, 
		glm::ivec2 const & WindowSize,
		glm::uint32 const & VersionMajor,
		glm::uint32 const & VersionMinor);
	virtual ~sample();

	virtual bool check() const;
    virtual bool begin(glm::ivec2 const & WindowSize);
    virtual bool end();
    virtual void render();

private:
	bool initProgram();
	bool initArrayBuffer();
	bool initVertexArray();
};

#endif//GLF_SAMPLE_INCLUDED