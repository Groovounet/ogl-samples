#version 330 core

#define ATTR_POSITION	0

uniform transform
{
	mat4 MVP;
} Transform;

layout(location = ATTR_POSITION) in vec3 Position;

void main()
{	
	gl_Position = Transform.MVP * vec4(Position, 1.0);
}
