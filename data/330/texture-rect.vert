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

uniform mat4 MVP;

in attr
{
	layout(location = ATTR_POSITION) vec2 Position;
	layout(location = ATTR_TEXCOORD) vec2 Texcoord;
} Attr;

out vert
{
	/*layout(location = VERT_POSITION)*/ vec4 gl_Position;
	/*layout(location = VERT_TEXCOORD)*/ vec2 Texcoord;
} Vert;

void main()
{	
	Vert.Texcoord = Attr.Texcoord;
	gl_Position = MVP * vec4(Attr.Position, 0.0, 1.0);
}