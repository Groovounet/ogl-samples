#version 330 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

uniform sampler2D DiffuseA;
uniform sampler2D DiffuseB;

in block
{
	vec2 Texcoord;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = (texture(DiffuseA, In.Texcoord) + texture(DiffuseB, In.Texcoord)) * 0.5;
}
