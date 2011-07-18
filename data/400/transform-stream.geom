#version 400 core

#define POSITION	0
#define COLOR		3
#define FRAG_COLOR	0

layout(triangle_strip, max_vertices = 4) out;
precision highp float;

in block
{
	vec4 Color;
} In[];

out block
{
	layout(stream = 0) vec4 StripPosition;
	layout(stream = 0) vec4 StripColor;
	layout(stream = 1) vec4 PointPosition;
	layout(stream = 1) vec4 PointColor;
} Out;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		Out.StripPosition = gl_in[i].gl_Position - vec4(0.0, 0.0, 0.1, 0.0);
		Out.StripColor = In[i].Color * 0.5 + 0.5;
		EmitStreamVertex(0);
	}
	EndStreamPrimitive(0);

	for(int i = 0; i < gl_in.length(); ++i)
	{
		Out.PointPosition = gl_in[i].gl_Position + vec4(0.0, 0.0, 0.2, 0.0);
		Out.PointColor = In[i].Color;
		EmitStreamVertex(1);
	}
	EndStreamPrimitive(1);
}
