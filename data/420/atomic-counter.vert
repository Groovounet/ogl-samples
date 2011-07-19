#version 330 core

uniform transform
{
	mat4 MVP;
} Transform;

in vec3 Position;

void main()
{	
	gl_Position = Transform.MVP * vec4(Position, 1.0);
}
