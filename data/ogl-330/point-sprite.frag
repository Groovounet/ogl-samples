#version 330 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0

uniform sampler2D Diffuse;

in block
{
	vec4 Color;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = In.Color * texture(Diffuse, gl_PointCoord);
}

