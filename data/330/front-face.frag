#version 330 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define VERT_POSITION	0
#define VERT_COLOR		3
#define VERT_TEXCOORD	4
#define VERT_INSTANCE	7
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

const vec4 FrontColor = vec4(1.0, 0.5, 0.0, 1.0);
const vec4 BackColor = vec4(0.0, 0.5, 1.0, 1.0);

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = gl_FrontFacing ? FrontColor : BackColor;
}

