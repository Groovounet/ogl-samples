#version 410 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

uniform sampler2D Diffuse;

in vert
{
	vec2 Texcoord;
} Vert;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	vec2 Size = textureSize(Diffuse, 0) - 1;
	vec2 Texcoord = Vert.Texcoord * Size;
	ivec2 Coord = ivec2(Vert.Texcoord * Size);
	
	vec4 Texel00 = texelFetch(Diffuse, Coord + ivec2(0, 0), 0);
	vec4 Texel10 = texelFetch(Diffuse, Coord + ivec2(1, 0), 0);
	vec4 Texel11 = texelFetch(Diffuse, Coord + ivec2(1, 1), 0);
	vec4 Texel01 = texelFetch(Diffuse, Coord + ivec2(0, 1), 0);
	
	vec4 Texel0 = mix(Texel00, Texel01, fract(Texcoord.y));
	vec4 Texel1 = mix(Texel10, Texel11, fract(Texcoord.y));
	FragColor  = mix(Texel0, Texel1, fract(Texcoord.x));
}

