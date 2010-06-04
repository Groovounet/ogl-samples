#version 330

uniform mat4 MVP;

in vec2 Position;
flat out int Instance;

void main()
{	
	Instance = gl_InstanceID;
	float Displacement = mix(-0.4, 0.4, gl_InstanceID / 5.0);
	gl_Position = MVP * vec4(Position, Displacement, 1.0);
}
