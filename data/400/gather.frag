#version 400 core

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

in vert
{
	/*layout(location = VERT_TEXCOORD)*/ vec2 Texcoord;
} Vert;

layout(location = FRAG_COLOR) out vec4 Color;

void main()
{
	vec2 Level = textureQueryLOD(Diffuse, Vert.Texcoord);
	
	ivec2 SizeMax = textureSize(Diffuse, floor(Level.x));
	ivec2 SizeMin = textureSize(Diffuse, ceil(Level.x));
	vec2 StepMax = 1.0 / vec2(SizeMax);
	vec2 StepMin = 1.0 / vec2(SizeMin);
	vec2 Step = mix(StepMax, StepMin, frac(Level.x));
	vec2 Coord = Vert.Texcoord
	
	vec4 R = textureGather(Diffuse, Vert.Texcoord, 0);
	vec4 G = textureGather(Diffuse, Vert.Texcoord, 1);
	vec4 B = textureGather(Diffuse, Vert.Texcoord, 2);
	
	vec3 Texel00(R.x, G.x, B.x); 
	vec3 Texel10(R.y, G.y, B.y); 
	vec3 Texel11(R.z, G.z, B.z); 
	vec3 Texel01(R.w, G.w, B.w); 
	vec3 Texel0(mix(Texel00, Texel01), Offset.y);
	vec3 Texel1(mix(Texel10, Texel11), Offset.y);
	
	Color = vec4(mix(Texel0, Texel1), Offset.x);
	//Color = vec4((R.x + R.y + R.z + R.w) * 0.25, (G.x + G.y + G.z + G.w) * 0.25, (B.x + B.y + B.z + B.w) * 0.25, 1.0);
}
