#version 410 core
#extension GL_ARB_shader_atomic_counters : enable

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

layout(binding = 0) uniform sampler2D Diffuse;
layout(binding = 0, offset = 0) uniform atomic_uint Atomic;

in block
{
	vec2 Texcoord;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = vec4(vec3((atomicCounterIncrement(Atomic) % 255) / 255.f), 1.0);
}
