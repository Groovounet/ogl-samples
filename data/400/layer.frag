#version 400 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

const vec4 Color[9] = vec4[]
(
	vec4(1.0, 0.0, 0.0, 1.0),
	vec4(0.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.5, 1.0, 1.0),
	vec4(1.0, 0.5, 0.5, 1.0),
	vec4(0.5, 1.0, 0.5, 1.0),
	vec4(0.5, 0.5, 1.0, 1.0),
	vec4(0.5, 0.0, 0.0, 1.0),
	vec4(0.0, 0.5, 0.0, 1.0),
	vec4(0.0, 0.0, 0.5, 1.0)
);

flat in lowp int GeomInstance;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = Color[int(GeomInstance)];
}
