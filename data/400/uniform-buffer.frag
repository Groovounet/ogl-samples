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

uniform material
{
	vec4 Diffuse;
} Material[1];

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = Material[0].Diffuse;
}
