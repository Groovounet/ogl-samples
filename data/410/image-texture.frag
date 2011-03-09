#version 410 core
//#extension GL_NV_gpu_shader5 : enable
#extension GL_EXT_shader_image_load_store : enable

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

layout(size1x32) coherent uniform image2D ImageData;
uniform uvec2 ImageSize;

in vert
{
	vec2 Texcoord;
} Vert;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	vec4 Texel = imageLoad(ImageData, ivec2(Vert.Texcoord * ImageSize));
	Color = Texel + vec4(Vert.Texcoord, 1.0, 1.0) * 1.0;
}
