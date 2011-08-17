#version 420 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define COMMON		0
#define FRAG_COLOR	0

#define MATERIAL	0
#define TRANSFORM0	1
#define TRANSFORM1	2	

layout(binding = TRANSFORM0) uniform transform
{
	mat4 MVP;
} Transform;

layout(location = POSITION) in vec2 Position;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{	
	gl_Position = Transform.MVP * vec4(Position, 0.0, 1.0);
}