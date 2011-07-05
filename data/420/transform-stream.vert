#version 410 core

#define POSITION	0
#define COLOR		3
#define FRAG_COLOR	0

uniform mat4 MVP;

layout(location = POSITION) in vec4 Position;

out block
{
	vec4 Color;
} Out;

void main()
{	
	gl_Position = MVP * vec4(vec2(Position), float(gl_InstanceID) * 0.25 - 0.5, 1.0);
	Out.Color = vec4(clamp(vec2(Position), 0.0, 1.0), 0.0, 1.0);
}
