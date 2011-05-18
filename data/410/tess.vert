#version 410 core

#define POSITION		0
#define COLOR			3
#define FRAG_COLOR		0

uniform mat4 MVP;

layout(location = POSITION) in vec2 Position;
layout(location = COLOR) in vec4 Color;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

out vec4 VertColor;

void main()
{	
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
	VertColor = Color;
}
