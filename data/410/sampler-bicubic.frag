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

mat4 const Hermite = mat4(
	vec4(0,-1, 2,-1), 
	vec4(2, 0,-5, 3),
	vec4(0, 1, 4,-3),
	vec4(0, 0,-1, 1));

vec4 hermite(in vec4 A, in vec4 B, in vec4 C, in vec4 D, in float s)
{
	vec4 Expo = vec4(1, s, s * s, s * s * s);

	return 0.5 * Expo * Hermite * mat4(
		A[0], B[0], C[0], D[0],
		A[1], B[1], C[1], D[1],
		A[2], B[2], C[2], D[2],
		A[3], B[3], C[3], D[3]);
}

void main()
{
	vec4 Texel00 = textureOffset(Diffuse, Vert.Texcoord, ivec2(-1,-1));
	vec4 Texel10 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 0,-1));
	vec4 Texel20 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 1,-1));
	vec4 Texel30 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 2,-1));

	vec4 Texel01 = textureOffset(Diffuse, Vert.Texcoord, ivec2(-1, 0));
	vec4 Texel11 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 0, 0));
	vec4 Texel21 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 1, 0));
	vec4 Texel31 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 2, 0));

	vec4 Texel02 = textureOffset(Diffuse, Vert.Texcoord, ivec2(-1, 1));
	vec4 Texel12 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 0, 1));
	vec4 Texel22 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 1, 1));
	vec4 Texel32 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 2, 1));

	vec4 Texel03 = textureOffset(Diffuse, Vert.Texcoord, ivec2(-1, 2));
	vec4 Texel13 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 0, 2));
	vec4 Texel23 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 1, 2));
	vec4 Texel33 = textureOffset(Diffuse, Vert.Texcoord, ivec2( 2, 2));

	vec2 TexelCoord = Vert.Texcoord * textureSize(Diffuse, 0) - 1;
	vec2 SplineCoord = fract(TexelCoord);

	vec4 Row0 = hermite(Texel00, Texel10, Texel20, Texel30, SplineCoord.x);
	vec4 Row1 = hermite(Texel01, Texel11, Texel21, Texel31, SplineCoord.x);
	vec4 Row2 = hermite(Texel02, Texel12, Texel22, Texel32, SplineCoord.x);
	vec4 Row3 = hermite(Texel03, Texel13, Texel23, Texel33, SplineCoord.x);

	FragColor = hermite(Row0, Row1, Row2, Row3, SplineCoord.y);
}

