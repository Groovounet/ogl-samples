#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define VERT_BLOCK		0
#define FRAG_COLOR		0

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 4) out;

struct vertex
{
	vec4 Color;
};

layout(location = VERTEX) in vertex Input[];
layout(location = VERTEX) out vertex Output;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		Output.Color = Input[i].Color;
		EmitVertex();
	}
	EndPrimitive();
}

