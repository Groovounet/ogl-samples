#version 330

uniform samplerBuffer Displacement;
uniform mat4 MVP;

in vec2 Position;
flat out mediump int Instance;

void main()
{	
	Instance = gl_InstanceID;
	gl_Position = MVP * (vec4(Position, 0.0, 0.0) + texelFetch(Displacement, gl_InstanceID));
}
