#version 420 core

#define FRAG_COLOR		0
#define DIFFUSE			0

layout(binding = DIFFUSE, rgba8) coherent uniform image2D Diffuse;
uniform uvec2 ImageSize;

in block
{
	vec2 Texcoord;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = imageLoad(Diffuse, ivec2(In.Texcoord * ImageSize));
}
