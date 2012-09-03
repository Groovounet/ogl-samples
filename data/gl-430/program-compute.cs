#version 430 core
#extension GL_ARB_compute_shader : require
#extension GL_ARB_shader_storage_buffer_object : require

#define TRANSFORM0		1

#define BUFFER_INPUT	0
#define BUFFER_OUTPUT	1

layout(binding = TRANSFORM0) uniform transform
{
	mat4 MVP;
} Transform;

struct vertex
{
	vec4 Position;
	vec4 Texcoord;
	vec4 Color;
};

layout(binding = BUFFER_INPUT) buffer iBuffer
{
	vertex Input[];
} In;

layout(binding = BUFFER_OUTPUT) buffer oBuffer
{
	vertex Ouput[];
} Out;

void main()
{	
	Out.Ouput[gl_LocalInvocationIndex].Position = In.Input[gl_LocalInvocationIndex].Position;
	//Out.Ouput[gl_LocalInvocationIndex].Position = Transform.MVP * In.Input[gl_LocalInvocationIndex].Position;
	Out.Ouput[gl_LocalInvocationIndex].Texcoord = In.Input[gl_LocalInvocationIndex].Texcoord;
	Out.Ouput[gl_LocalInvocationIndex].Color = In.Input[gl_LocalInvocationIndex].Color;
}
