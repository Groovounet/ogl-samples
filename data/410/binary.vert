#version 410 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

struct vertex
{
	vec2 Texcoord;
	vec3 Color;
};

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 Position;
layout(location = ATTR_TEXCOORD) in vec2 Texcoord;
out vertex Vertex;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{	
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
	Vertex.Texcoord = Texcoord;
	Vertex.Color = vec3(1.0, 0.9, 0.8);
}

