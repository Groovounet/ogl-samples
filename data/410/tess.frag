#version 410 core

#define POSITION		0
#define COLOR			3
#define FRAG_COLOR		0

in vec4 GeomColor;
layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = GeomColor;
}
