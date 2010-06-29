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

layout(location = ATTR_POSITION) in vec2 Position;
layout(location = ATTR_TEXCOORD) in vec2 Texcoord;

out vert
{
	vec2 Texcoord;
<<<<<<< HEAD
	float Instance;
=======
>>>>>>> 34b421353f4e0f9265b7901c09b4c34aa1abedba
} Vert;

void main()
{	
<<<<<<< HEAD
	Vert.Instance = gl_InstanceID;
	Vert.Texcoord = Texcoord;
	gl_Position = MVP * vec4(Position.x + Vert.Instance * 2.4 - 1.2, Position.y, 0.0, 1.0);
=======
	Vert.Texcoord = Texcoord;
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
>>>>>>> 34b421353f4e0f9265b7901c09b4c34aa1abedba
}
