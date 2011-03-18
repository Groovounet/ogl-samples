#version 400 core

#define FRAG_COLOR		0

uniform vec4 Diffuse;

in vec3 GeomColor;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = vec4(GeomColor, 1.0) * Diffuse;
}

