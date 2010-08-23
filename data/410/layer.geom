#version 410 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define INSTANCE		7
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

layout(triangles, invocations = 4) in;
layout(triangle_strip, max_vertices = 3) out;

layout(location = INSTANCE) flat out int Instance;

uniform mat4 MVP;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = MVP * gl_in[i].gl_Position;
		gl_Layer = gl_InvocationID;
		Instance = gl_InvocationID;
		EmitVertex();
	}

	EndPrimitive();
}

