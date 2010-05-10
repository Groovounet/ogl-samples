#version 330 core

precision highp float;
precision highp int;

uniform mat4 MVP;

in vec2 Position;
out float VertInstance;

void main()
{	
	gl_Position = MVP * vec4(Position, float(gl_InstanceID) * 0.25 - 0.5, 1.0);
	VertInstance = float(gl_InstanceID);
}