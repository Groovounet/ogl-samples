#version 410 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

uniform dmat4 MVP;

layout(location = ATTR_POSITION) in dvec2 Position;

void main()
{	
	gl_Position = vec4(MVP * dvec4(Position, 0.0, 1.0));
}

