#version 330 core

layout(triangle_strip, max_vertices = 4) out;
precision highp float;

in block
{
	vec4 Color;
} In[];

out block
{
	vec4 Color;
} Out;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		Out.Color = In[i].Color;
		EmitVertex();
	}
	EndPrimitive();
}

