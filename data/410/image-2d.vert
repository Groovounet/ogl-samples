#version 410 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

precision highp int;

struct vertex
{
	vec2 Texcoord;
};

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 Position;
layout(location = ATTR_TEXCOORD) in vec2 Texcoord;

out vertex Vertex;

void main()
{	
	Vertex.Texcoord = Texcoord;
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
}