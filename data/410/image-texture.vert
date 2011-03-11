#version 410 core

#define ATTR_POSITION	0
#define ATTR_TEXCOORD	4

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 Position;
layout(location = ATTR_TEXCOORD) in vec2 Texcoord;

out vertex
{
	vec2 Texcoord;
} Vertex;

void main()
{	
	Vertex.Texcoord = Texcoord;
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
}