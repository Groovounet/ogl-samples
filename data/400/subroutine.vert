#version 400 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0

uniform mat4 MVP;
uniform float Displacement;

layout(location = POSITION) in vec2 Position;
layout(location = TEXCOORD) in vec2 Texcoord;

layout(location = TEXCOORD) out vec2 VertTexcoord;

void main()
{	
	VertTexcoord = Texcoord;
	gl_Position = MVP * vec4(Position, Displacement, 1.0);
}

