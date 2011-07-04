#version 410 core
#extension GL_ARB_shader_image_load_store : enable

#define FRAG_COLOR		0

layout(rgba8) coherent uniform uimage2D ImageData;
uniform uvec2 ImageSize;

struct vertex
{
	vec2 Texcoord;
};

in vertex Vertex;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = imageLoad(ImageData, ivec2(Vertex.Texcoord * ImageSize)).x;
}
