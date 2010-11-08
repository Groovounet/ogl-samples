#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define FRAG_COLOR		0

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec2 AttrPosition;
layout(location = ATTR_COLOR) in vec4 AttrColor;

out vec4 VertColor;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{	
	gl_Position = MVP * vec4(AttrPosition, 0.0, 1.0);
	VertColor = AttrColor;
}
