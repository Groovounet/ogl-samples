#version 400 core

#define FRAG_COLOR		0

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

in custom
{
	vec4 Color;
} Prim;

void main()
{
	Color = Prim.Color;
}
