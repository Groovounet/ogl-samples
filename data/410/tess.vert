#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define VERT_BLOCK		0
#define FRAG_COLOR		0

uniform mat4 MVP;

struct vertex
{
	vec4 Color;
};

layout(location = ATTR_POSITION) in vec2 Position;
layout(location = ATTR_COLOR) in vec4 Color;

layout(location = VERT_BLOCK) out vertex Output;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{	
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
	Output.Color = Color;
}
