#version 330 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0

const vec3 Attenuation = vec3(0, 1, 0);

uniform mat4 MVP;
uniform mat4 MV;

layout(location = POSITION) in vec2 Position;
layout(location = COLOR) in vec4 Color;

out block
{
	vec4 Color;
} Out;

void main()
{	
	float Distance = 1;

	Out.Color = Color;
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
	gl_PointSize = 256.f / -(MV * vec4(Position, 0.0, 1.0)).z;
}
