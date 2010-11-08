#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define FRAG_COLOR		0

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 4) out;

in vec4 EvalColor[];
out vec4 GeomColor;

in gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
} gl_in[];

out gl_PerVertex 
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		GeomColor = EvalColor[i];
		EmitVertex();
	}
	EndPrimitive();
}

