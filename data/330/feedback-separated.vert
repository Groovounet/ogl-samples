#version 330 core

#define ATTR_POSITION	0

layout(location = ATTR_POSITION) in vec4 Position;

void main()
{	
	gl_Position = Position;
}

