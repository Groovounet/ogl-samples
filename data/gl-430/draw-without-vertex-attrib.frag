#version 420 core

#define FRAG_COLOR		0

const vec4 Diffuse = vec4(1.0, 0.5, 0.0, 1.0);

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = Diffuse;
}

