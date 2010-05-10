#version 330 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define VERT_POSITION	0
#define VERT_COLOR		3
#define VERT_TEXCOORD	4
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 Position;
layout(location = ATTR_COLOR) in vec4 Color;

/*layout(location = VERT_COLOR)*/ out vec4 VertColor;

void main()
{	
	gl_Position = MVP * vec4(Position, float(gl_InstanceID) * 0.25 - 0.5, 1.0);
	VertColor = Color;
}