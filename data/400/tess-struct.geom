#version 400 core

layout(triangles, invocations = 1) in;

struct vertex
{
	vec4 Color;
};

in vertex Eval[];
out vertex Prim;

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

