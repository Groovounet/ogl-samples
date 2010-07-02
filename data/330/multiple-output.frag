#version 330 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define VERT_POSITION	0
#define VERT_COLOR		3
#define VERT_TEXCOORD	4
#define VERT_INSTANCE	7
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

layout(location = FRAG_RED, index = 0) out vec4 Red;
layout(location = FRAG_GREEN, index = 0) out vec4 Green;
layout(location = FRAG_BLUE, index = 0) out vec4 Blue;

void main()
{
	Red = vec4(1.0, 0.0, 0.0, 1.0);
	Green = vec4(0.0, 1.0, 0.0, 1.0);
	Blue = vec4(0.0, 0.0, 1.0, 1.0);
}
