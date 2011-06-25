#version 330 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

precision highp float;

uniform mat4 MVP;

layout(location = POSITION) in vec2 Position;
layout(location = COLOR) in vec4 Color;
layout(location = COLOR) out vec4 VertColor;

void main()
{	
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
	VertColor = Color;
}

