#version 330 core

uniform mat4 MVP;

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
	gl_Position = MVP * vec4(Position[gl_VertexID], 0.0, 1.0);
}

