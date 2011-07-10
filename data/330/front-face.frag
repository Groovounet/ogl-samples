#version 330 core

#define POSITION		0
#define COLOR			3
#define TEXCOORD		4
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

const vec4 FrontColor = vec4(1.0, 0.5, 0.0, 1.0);
const vec4 BackColor = vec4(0.0, 0.5, 1.0, 1.0);

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = gl_FrontFacing ? FrontColor : BackColor;
}

