#version 400 core

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

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

subroutine vec4 diffuse();

subroutine(diffuse)
vec4 orange()
{
	return vec4(1.0, 0.5, 0.0, 1.0);
}

subroutine(diffuse)
vec4 blue()
{
	return vec4(0.0, 0.5, 1.0, 1.0);
}

subroutine uniform diffuse Diffuse;

void main()
{
	Color = Diffuse();
}
