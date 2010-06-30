#version 400 core

uniform transform
{
	mat4 MVP;
} Transform[2];

in vec3 Position;

void main()
{	
	gl_Position = Transform[gl_InstanceID].MVP * vec4(Position, 1.0);
}
