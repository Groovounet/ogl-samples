#version 410 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

uniform sampler2DArray Diffuse;

in vec2 GeomTexcoord;
flat in int GeomInstance;
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(Diffuse, vec3(GeomTexcoord, GeomInstance));
}
