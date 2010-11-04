#version 410 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

layout(triangles, invocations = 4) in;
layout(triangle_strip, max_vertices = 3) out;

flat out int GeomInstance;

uniform mat4 MVP;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = MVP * gl_in[i].gl_Position;
		gl_Layer = gl_InvocationID;
		GeomInstance = gl_InvocationID;
		EmitVertex();
	}

	EndPrimitive();
}

