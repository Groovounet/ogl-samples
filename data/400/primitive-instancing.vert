#version 400 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4

layout(location = ATTR_POSITION) in vec3 Position;
out vec3 VertColor;

void main()
{	
	gl_Position = vec4(Position, 1.0);
	VertColor = vec3(1.0, 0.5, 0.0);
}

