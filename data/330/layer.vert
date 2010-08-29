#version 330 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

layout(location = ATTR_POSITION) in vec2 Position;

void main()
{	
	gl_Position = vec4(Position, 0.0, 1.0);
}

