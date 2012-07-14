#version 420 core

#define TRANSFORM0	1

layout(binding = TRANSFORM0) uniform transform
{
	mat4 MVP;
} Transform;

const int VertexCount = 6;
const vec2 Position[VertexCount] = vec2[](
	vec2(-1.0f,-1.0f),
	vec2( 1.0f,-1.0f),
	vec2( 1.0f, 1.0f),
	vec2(-1.0f,-1.0f),
	vec2( 1.0f, 1.0f),
	vec2(-1.0f, 1.0f));

void main()
{	
	gl_Position = Transform.MVP * vec4(Position[gl_VertexID], 0.0, 1.0);
}

