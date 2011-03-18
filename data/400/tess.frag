#version 400 core

#define FRAG_COLOR		0

in vec4 GeomColor;
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = GeomColor;
}
