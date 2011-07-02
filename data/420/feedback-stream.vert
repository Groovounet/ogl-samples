#version 410 core

#define POSITION	0
#define COLOR		3
#define FRAG_COLOR	0

layout(location = POSITION) in vec4 Position;
layout(location = COLOR) in vec4 Color;

out block
{
	vec4 Color;
} Out;

void main()
{	
	gl_Position = Position + vec4(0, 0, float(gl_InstanceID) * 0.25 - 0.5, 0);
	Out.Color = Color;
}

