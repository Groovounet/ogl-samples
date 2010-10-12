#version 400 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

uniform sampler2D DiffuseDXT1;
uniform sampler2D DiffuseRGB8;

in vec2 Texcoord;

subroutine vec4 diffuse();

subroutine(diffuse)
vec4 diffuseLQ()
{
	return texture(DiffuseDXT1, Texcoord);
}

subroutine(diffuse)
vec4 diffuseHQ()
{
	return texture(DiffuseRGB8, Texcoord);
}

subroutine uniform diffuse Diffuse;

void main()
{
	Color = Diffuse();
}
