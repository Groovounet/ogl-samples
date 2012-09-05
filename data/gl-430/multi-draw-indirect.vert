#version 420 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0

#define TRANSFORM0	1

layout(binding = 0, offset = 0) uniform atomic_uint DrawID;

layout(binding = TRANSFORM0) uniform transform
{
	mat4 MVP;
} Transform;

layout(location = POSITION) in vec3 Position;
layout(location = TEXCOORD) in vec3 Texcoord;

out gl_PerVertex
{
    vec4 gl_Position;
};

out block
{
	vec2 Texcoord;
	vec4 Color;
	flat uint DrawID;
} Out;

void main()
{
	if(gl_VertexID == 0 && gl_InstanceID == 0)
	{
		Out.DrawID = atomicCounterIncrement(DrawID);
		Out.Color = vec4(1.0, 0.5, 0.0, 1.0);
	}
	else
	{
		Out.DrawID = atomicCounter(DrawID);
		Out.Color = vec4(0.0, 0.5, 1.0, 1.0);
	}
	Out.Texcoord = Texcoord.st;
	gl_Position = Transform.MVP * vec4(Position, 1.0);

	memoryBarrier();
}
