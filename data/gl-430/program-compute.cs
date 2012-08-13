#version 430 core
#extension GL_ARB_compute_shader : require
#extension GL_ARB_shader_storage_buffer_object : require

#define TRANSFORM0		1

#define BUFFER_INPUT	0
#define BUFFER_OUTPUT	1

//layout(binding = TRANSFORM0) uniform transform
//{
//	mat4 MVP;
//} Transform;

struct vertex
{
	vec2 Position;
	vec2 Texcoord;
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
	Out.Ouput[gl_LocalInvocationIndex].Texcoord = In.Input[gl_LocalInvocationIndex].Texcoord;
	Out.Ouput[gl_LocalInvocationIndex].Position = In.Input[gl_LocalInvocationIndex].Position;
	//Out.Ouput[gl_LocalInvocationIndex].Position = vec2(Transform.MVP * vec4(In.Input[gl_LocalInvocationIndex].Position, 0.0, 1.0));
}
