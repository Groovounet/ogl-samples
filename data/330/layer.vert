#version 330 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0

precision highp int;

layout(location = POSITION) in vec2 Position;

void main()
{	
	gl_Position = vec4(Position, 0.0, 1.0);
}

