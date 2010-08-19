#version 400 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

layout(triangles, invocations = 3) in;

flat out lowp int GeomInstance;

uniform mat4 MVP;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = MVP * gl_in[i].gl_Position;
		EmitVertex();
	}

	gl_Layer = gl_InvocationID;
	GeomInstance = gl_InvocationID;

	EndPrimitive();
}

