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

uniform sampler2DArray Diffuse;
<<<<<<< HEAD
=======
uniform float Layer;
>>>>>>> 34b421353f4e0f9265b7901c09b4c34aa1abedba

in vert
{
	vec2 Texcoord;
<<<<<<< HEAD
	float Instance;
=======
>>>>>>> 34b421353f4e0f9265b7901c09b4c34aa1abedba
} Vert;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
<<<<<<< HEAD
	Color = texture(Diffuse, vec3(Vert.Texcoord, Vert.Instance));
=======
	Color = texture(Diffuse, vec3(Vert.Texcoord, Layer));
>>>>>>> 34b421353f4e0f9265b7901c09b4c34aa1abedba
}
