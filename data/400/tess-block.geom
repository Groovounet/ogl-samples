#version 400 core

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 4) out;

in custom
{
	vec4 Color;
} Eval[];

out custom
{
	vec4 Color;
} Prim;

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

