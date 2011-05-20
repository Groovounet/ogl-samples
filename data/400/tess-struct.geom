#version 400 core

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 4) out;

struct vertex
{
	vec4 Color;
};

layout(location = 0) in vertex Eval[];
layout(location = 0) out vertex Prim;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		Prim.Color = Eval[i].Color;
		EmitVertex();
	}
	EndPrimitive();
}

