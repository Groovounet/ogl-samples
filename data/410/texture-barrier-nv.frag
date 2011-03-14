#version 410 core

#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

precision highp int;

uniform sampler2D Diffuse;

in vec4 gl_FragCoord;
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	vec2 TextureSize = vec2(textureSize(Diffuse, 0));
	vec2 Texcoord = vec2(gl_FragCoord.x / TextureSize.x, gl_FragCoord.y / TextureSize.y);

	FragColor = texture(Diffuse, Texcoord) - 1.0 / 255;
}
