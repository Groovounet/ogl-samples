#version 420 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

layout(location = POSITION) in vec4 Position;
layout(location = TEXCOORD) in vec2 Texcoord;

out gl_PerVertex
{
	vec4 gl_Position;
};

out block
{
	vec2 Texcoord;
} Out;

void main()
{	
	Out.Texcoord = Texcoord;
	gl_Position = Position;
}
