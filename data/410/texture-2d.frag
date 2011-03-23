#version 410 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

precision highp int;

struct vertex
{
	vec2 Texcoord;
};

uniform sampler2D Diffuse;

in vertex Vertex;
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(Diffuse, Vertex.Texcoord);
}
