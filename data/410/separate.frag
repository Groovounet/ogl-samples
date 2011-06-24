#version 410 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define VERTEX		0
#define FRAG_COLOR	0

struct vertex
{
	vec2 Texcoord;
	vec3 Color;
};

uniform sampler2D Diffuse;

layout(location = VERTEX) in vertex In;
layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = texture(Diffuse, In.Texcoord) * vec4(In.Color, 1.0);
}
