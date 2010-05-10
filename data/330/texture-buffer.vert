#version 140

uniform samplerBuffer Displacement;
uniform mat4 MVP;

in vec2 Position;
in vec2 Texcoord;

out vec2 VertTexcoord;

void main()
{	
	VertTexcoord = Texcoord;
	vec4 Fetch = texelFetchBuffer(Displacement, gl_InstanceID);
	gl_Position = MVP * (vec4(Position, 0.0, 1.0) + Fetch);
}
