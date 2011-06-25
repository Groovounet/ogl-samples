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

uniform sampler2D Diffuse;

in block
{
	vec2 Texcoord;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	vec2 Size = textureSize(Diffuse, 0) - 1;
	vec2 Texcoord = In.Texcoord * Size;
	ivec2 Coord = ivec2(In.Texcoord * Size);
	
	vec4 Texel00 = texelFetch(Diffuse, Coord + ivec2(0, 0), 0);
	vec4 Texel10 = texelFetch(Diffuse, Coord + ivec2(1, 0), 0);
	vec4 Texel11 = texelFetch(Diffuse, Coord + ivec2(1, 1), 0);
	vec4 Texel01 = texelFetch(Diffuse, Coord + ivec2(0, 1), 0);
	
	vec4 Texel0 = mix(Texel00, Texel01, fract(Texcoord.y));
	vec4 Texel1 = mix(Texel10, Texel11, fract(Texcoord.y));
	Color  = mix(Texel0, Texel1, fract(Texcoord.x));
}
