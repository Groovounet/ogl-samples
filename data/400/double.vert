#version 400 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

uniform dmat4 MVP;

layout(location = ATTR_POSITION) in vec2 Position;

void main()
{	
	gl_Position = vec4(MVP * dvec4(Position, 0.0, 1.0));
}

