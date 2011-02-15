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

float luminosity(in vec3 color)
{
	return dot(color, vec3(0.33, 0.59, 0.11));
}

void main()
{
	FragColor = texture(Diffuse, Vert.Texcoord);
}

/*
vec4 textureCatmullrom(in sampler2D Sampler, in vec2 Texcoord)
{
	ivec2 TextureSize = textureSize(Sampler, 0) - ivec2(1);
	ivec2 TexelCoord = ivec2(TextureSize * Texcoord);

	vec4 Texel00 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1,-1));
	vec4 Texel10 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0,-1));
	vec4 Texel20 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1,-1));
	vec4 Texel30 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2,-1));

	vec4 Texel01 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1, 0));
	vec4 Texel11 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0, 0));
	vec4 Texel21 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1, 0));
	vec4 Texel31 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2, 0));

	vec4 Texel02 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1, 1));
	vec4 Texel12 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0, 1));
	vec4 Texel22 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1, 1));
	vec4 Texel32 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2, 1));

	vec4 Texel03 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1, 2));
	vec4 Texel13 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0, 2));
	vec4 Texel23 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1, 2));
	vec4 Texel33 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2, 2));

	vec2 SplineCoord = fract(TextureSize * Texcoord);

	vec4 Row0 = catmullRom(Texel00, Texel10, Texel20, Texel30, SplineCoord.x);
	vec4 Row1 = catmullRom(Texel01, Texel11, Texel21, Texel31, SplineCoord.x);
	vec4 Row2 = catmullRom(Texel02, Texel12, Texel22, Texel32, SplineCoord.x);
	vec4 Row3 = catmullRom(Texel03, Texel13, Texel23, Texel33, SplineCoord.x);

	return catmullRom(Row0, Row1, Row2, Row3, SplineCoord.y);
}

vec4 textureCatmullromApprox(in sampler2D Sampler, in vec2 Texcoord)
{
	ivec2 TextureSize = textureSize(Sampler, 0) - ivec2(1);
	ivec2 TexelCoord = ivec2(TextureSize * Vert.Texcoord);

	vec4 Texel00 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1,-1));
	vec4 Texel10 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0,-1));
	vec4 Texel20 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1,-1));
	vec4 Texel30 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2,-1));

	vec4 Texel01 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1, 0));
	vec4 Texel11 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0, 0));
	vec4 Texel21 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1, 0));
	vec4 Texel31 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2, 0));

	vec4 Texel02 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1, 1));
	vec4 Texel12 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0, 1));
	vec4 Texel22 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1, 1));
	vec4 Texel32 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2, 1));

	vec4 Texel03 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2(-1, 2));
	vec4 Texel13 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 0, 2));
	vec4 Texel23 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 1, 2));
	vec4 Texel33 = texelFetchOffset(Sampler, TexelCoord, 0, ivec2( 2, 2));

	vec2 SplineCoord = fract(TextureSize * Vert.Texcoord);

	vec4 Row0 = catmullRomApprox(Texel00, Texel10, Texel20, Texel30, SplineCoord.x - 0.125);
	vec4 Row1 = catmullRomApprox(Texel01, Texel11, Texel21, Texel31, SplineCoord.x - 0.125);
	vec4 Row2 = catmullRomApprox(Texel02, Texel12, Texel22, Texel32, SplineCoord.x - 0.125);
	vec4 Row3 = catmullRomApprox(Texel03, Texel13, Texel23, Texel33, SplineCoord.x - 0.125);

	vec4 Col0 = catmullRomApprox(Row0, Row1, Row2, Row3, SplineCoord.y - 0.125);
	vec4 Col1 = catmullRomApprox(Row0, Row1, Row2, Row3, SplineCoord.y + 0.125);

	vec4 Row4 = catmullRomApprox(Texel00, Texel10, Texel20, Texel30, SplineCoord.x + 0.125);
	vec4 Row5 = catmullRomApprox(Texel01, Texel11, Texel21, Texel31, SplineCoord.x + 0.125);
	vec4 Row6 = catmullRomApprox(Texel02, Texel12, Texel22, Texel32, SplineCoord.x + 0.125);
	vec4 Row7 = catmullRomApprox(Texel03, Texel13, Texel23, Texel33, SplineCoord.x + 0.125);

	vec4 Col2 = catmullRomApprox(Row4, Row5, Row6, Row7, SplineCoord.y - 0.125);
	vec4 Col3 = catmullRomApprox(Row4, Row5, Row6, Row7, SplineCoord.y + 0.125);

	vec2 BilinearCoord = fract(SplineCoord * 4.0);
	vec4 Linear0 = mix(Col0, Col1, BilinearCoord.y);
	vec4 Linear1 = mix(Col2, Col3, BilinearCoord.y);
	return mix(Linear0, Linear1, BilinearCoord.x);
}

void main()
{
	FragColor = textureCatmullrom(Diffuse, Vert.Texcoord) - textureCatmullromApprox(Diffuse, Vert.Texcoord);
}
*/
