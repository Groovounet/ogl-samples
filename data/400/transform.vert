#version 400 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define INSTANCE	7
#define FRAG_COLOR	0

layout(location = POSITION) in vec4 Position;

void main()
{	
	gl_Position = Position;
}
