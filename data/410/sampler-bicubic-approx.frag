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

const mat4 Hermite = mat4(
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

vec4 catmullRom(in vec4 A, in vec4 B, in vec4 C, in vec4 D, in float s)
{
	float s1 = s;
	float s2 = s * s;
	float s3 = s * s * s;

	float f1 = -s3 + 2.0 * s2 - s;
	float f2 = 3.0 * s3 - 5.0 * s2 + 2.0;
	float f3 = -3.0 * s3 + 4.0 * s2 + s;
	float f4 = s3 - s2;

	return (f1 * A + f2 * B + f3 * C + f4 * D) / 2.0;
}

vec4 cubic(in vec4 A, in vec4 B, in vec4 C, in vec4 D, in float s)
{
	return ((A * s + B) * s + C) * s + D;
}

void main()
{
	ivec2 TextureSize = textureSize(Diffuse, 0);
	ivec2 TexelCoord = ivec2(TextureSize * Vert.Texcoord);

	vec4 Texel00 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2(-1,-1));
	vec4 Texel10 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 0,-1));
	vec4 Texel20 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 1,-1));
	vec4 Texel30 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 2,-1));

	vec4 Texel01 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2(-1, 0));
	vec4 Texel11 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 0, 0));
	vec4 Texel21 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 1, 0));
	vec4 Texel31 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 2, 0));

	vec4 Texel02 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2(-1, 1));
	vec4 Texel12 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 0, 1));
	vec4 Texel22 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 1, 1));
	vec4 Texel32 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 2, 1));

	vec4 Texel03 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2(-1, 2));
	vec4 Texel13 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 0, 2));
	vec4 Texel23 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 1, 2));
	vec4 Texel33 = texelFetchOffset(Diffuse, TexelCoord, 0, ivec2( 2, 2));

	vec2 SplineCoord = fract(TextureSize * Vert.Texcoord);

	vec4 Row0 = hermite(Texel00, Texel10, Texel20, Texel30, SplineCoord.x);
	vec4 Row1 = hermite(Texel01, Texel11, Texel21, Texel31, SplineCoord.x);
	vec4 Row2 = hermite(Texel02, Texel12, Texel22, Texel32, SplineCoord.x);
	vec4 Row3 = hermite(Texel03, Texel13, Texel23, Texel33, SplineCoord.x);

	FragColor = hermite(Row0, Row1, Row2, Row3, SplineCoord.y);
}


/*
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

	vec2 TexelCoord = Vert.Texcoord * textureSize(Diffuse, 0);
	vec2 SplineCoord = fract(TexelCoord);

	vec4 Row0 = hermite(Texel00, Texel10, Texel20, Texel30, SplineCoord.x);
	vec4 Row1 = hermite(Texel01, Texel11, Texel21, Texel31, SplineCoord.x);
	vec4 Row2 = hermite(Texel02, Texel12, Texel22, Texel32, SplineCoord.x);
	vec4 Row3 = hermite(Texel03, Texel13, Texel23, Texel33, SplineCoord.x);

	FragColor = hermite(Row0, Row1, Row2, Row3, SplineCoord.y);
}
*/
/*
void main()
{
	ivec2 TextureSize = textureSize(Diffuse, 0);
	vec2 TextureSizeInv = 1.0 / TextureSize;

	vec4 Texel00 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-1.5,-1.5));
	vec4 Texel10 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-0.5,-1.5));
	vec4 Texel20 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 0.5,-1.5));
	vec4 Texel30 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 1.5,-1.5));

	vec4 Texel01 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-1.5,-0.5));
	vec4 Texel11 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-0.5,-0.5));
	vec4 Texel21 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 0.5,-0.5));
	vec4 Texel31 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 1.5,-0.5));

	vec4 Texel02 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-1.5, 0.5));
	vec4 Texel12 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-0.5, 0.5));
	vec4 Texel22 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 0.5, 0.5));
	vec4 Texel32 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 1.5, 0.5));

	vec4 Texel03 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-1.5, 1.5));
	vec4 Texel13 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2(-0.5, 1.5));
	vec4 Texel23 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 0.5, 1.5));
	vec4 Texel33 = texture(Diffuse, Vert.Texcoord + TextureSizeInv * vec2( 1.5, 1.5));

	vec2 TexelCoord = Vert.Texcoord * TextureSize;
	vec2 SplineCoord = fract(TexelCoord);

	vec4 Row0 = hermite(Texel00, Texel10, Texel20, Texel30, SplineCoord.x);
	vec4 Row1 = hermite(Texel01, Texel11, Texel21, Texel31, SplineCoord.x);
	vec4 Row2 = hermite(Texel02, Texel12, Texel22, Texel32, SplineCoord.x);
	vec4 Row3 = hermite(Texel03, Texel13, Texel23, Texel33, SplineCoord.x);

	FragColor = hermite(Row0, Row1, Row2, Row3, SplineCoord.y);
}
*/
