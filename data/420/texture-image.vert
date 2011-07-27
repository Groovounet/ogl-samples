#version 420 core

#define POSITION	0
#define TEXCOORD	4

uniform mat4 MVP;

layout(location = POSITION) in vec2 Position;
layout(location = TEXCOORD) in vec2 Texcoord;

out gl_PerVertex
{
    vec4 gl_Position;
};

struct vertex
{
	vec2 Texcoord;
};

out vertex Vertex;

void main()
{	
	Vertex.Texcoord = Texcoord;
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
}