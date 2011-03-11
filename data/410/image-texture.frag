#version 410 core
#extension GL_NV_gpu_shader5 : enable
#extension GL_EXT_shader_image_load_store : enable

#define FRAG_COLOR		0

layout(size1x32) coherent uniform image2D ImageData;
uniform uvec2 ImageSize;

struct vertex
{
	vec2 Texcoord;
};

in vertex Vertex;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = imageLoad(ImageData, ivec2(Vertex.Texcoord * ImageSize)).bgra;
}
