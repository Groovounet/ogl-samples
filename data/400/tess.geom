#version 400 core

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 4) out;

in vec4 EvalColor[];
out vec4 GeomColor;

void main()
{	
	GeomColor = vec4(0);

	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		GeomColor = EvalColor[i];
		EmitVertex();
	}
	EndPrimitive();
}

