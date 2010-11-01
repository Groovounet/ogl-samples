#version 330 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

precision highp float;

in vec4 VertColor;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = VertColor;
}

