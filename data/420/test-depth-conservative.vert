#version 420 core

#define POSITION	0

uniform mat4 MVP;

layout(location = POSITION) in vec2 Position;

out gl_PerVertex
{
	vec4 gl_Position;
};

out block
{
	float Instance;
} Out;

void main()
{	
	gl_Position = MVP * vec4(Position, float(gl_InstanceID) * 0.25 - 0.5, 1.0);
	Out.Instance = float(gl_InstanceID);
}
