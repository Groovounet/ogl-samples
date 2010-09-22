#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define VERT_BLOCK		0
#define FRAG_COLOR		0

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

struct vertex
{
	vec4 Color;
};

layout(location = VERTEX) in vertex Input;

void main()
{
	Color = Input.Color;
}
