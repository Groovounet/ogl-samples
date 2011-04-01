#version 410 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0

uniform vec4 Diffuse;

layout(location = COLOR) in vec3 Color;
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = vec4(Color, 1.0) * Diffuse;
}

