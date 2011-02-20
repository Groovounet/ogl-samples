#version 330 core
#define FRAG_COLOR		0

uniform sampler2DMS Diffuse;

in vert
{
	vec2 Texcoord;
} Vert;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	// integer UV coordinates, needed for fetching multisampled texture
	ivec2 Texcoord = ivec2(textureSize(Diffuse) * Vert.Texcoord);

	Color = texelFetch(Diffuse, Texcoord, 0);
}
