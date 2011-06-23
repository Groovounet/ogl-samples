#version 330 core

#define ATTR_POSITION	0

uniform mat4 MVP;

layout(location = ATTR_POSITION) in vec4 Position;

void main()
{	
	gl_Position = MVP * Position;
}
