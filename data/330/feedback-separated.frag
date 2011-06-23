#version 330 core

#define FRAG_COLOR		0

uniform vec4 Diffuse;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = Diffuse;
}

