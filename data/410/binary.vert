#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 AttrPosition;
layout(location = ATTR_TEXCOORD) in vec2 AttrTexcoord;

out vec2 Texcoord;
out vec3 Color;

void main()
{	
	gl_Position = MVP * vec4(AttrPosition, 0.0, 1.0);
	Texcoord = AttrTexcoord;
	Color = vec3(1.0, 0.9, 0.8);
}

