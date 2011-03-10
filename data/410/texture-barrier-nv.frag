#version 410 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

uniform sampler2D Diffuse;

in vec4 gl_FragCoord;
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	vec2 TextureSize = vec2(textureSize(Diffuse, 0));
	vec2 Texcoord = vec2(gl_FragCoord.x / TextureSize.x, gl_FragCoord.y / TextureSize.y);

	FragColor = texture(Diffuse, Texcoord) - 1.0 / 255;
/*
	vec4 TexelO = textureOffset(Diffuse, Texcoord, ivec2( 0, 0)) * 4;
	vec4 TexelA = textureOffset(Diffuse, Texcoord, ivec2( 1, 0)) * 1;
	vec4 TexelB = textureOffset(Diffuse, Texcoord, ivec2(-1, 0)) * 1;
	vec4 TexelC = textureOffset(Diffuse, Texcoord, ivec2( 0, 1)) * 1;
	vec4 TexelD = textureOffset(Diffuse, Texcoord, ivec2( 0,-1)) * 1;
	FragColor = (TexelO + TexelA + TexelB + TexelC + TexelD) / 8;
*/
}
