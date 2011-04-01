#version 410 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

precision highp int;

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 Position;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{	
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
}