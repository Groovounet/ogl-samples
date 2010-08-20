#version 410 core

precision mediump int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define VERT_POSITION	0
#define VERT_COLOR		3
#define VERT_TEXCOORD	4
#define VERT_INSTANCE	7
#define GEOM_TEXCOORD	4
#define GEOM_INSTANCE	7
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

layout(triangles, invocations = 4) in;

layout(location = VERT_TEXCOORD) in vec2 Texcoord;
layout(location = GEOM_TEXCOORD) out vec2 GeomTexcoord;
layout(location = GEOM_INSTANCE) out int GeomInstance;

uniform mat4 MVP;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = MVP * gl_in[i].gl_Position;
		gl_Layer = gl_InvocationID;
		gl_ViewportIndex = gl_InvocationID;
		GeomInstance = gl_InvocationID;
		GeomTexcoord = Texcoord;
		EmitVertex();
	}

	EndPrimitive();
}

