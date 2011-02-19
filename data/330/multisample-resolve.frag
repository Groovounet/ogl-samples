#version 330 core
#define FRAG_COLOR		0

uniform sampler2DMS Diffuse;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;
in vec2 Texcoord;

void main()
{
	// integer UV coordinates, needed for fetching multisampled texture
	ivec2 iUV = ivec2(textureSize(Diffuse) * Texcoord);
	
	// Low range value of the pixel, after box filter
	vec4 Temp = vec4(0,0,0,0);
	
	// For each of the 4 samples
	for(int i = 0; i < 4; ++i)
		Temp += texelFetch(Diffuse, iUV, i) *= 0.25;

	// Output color is the resolved value, gamma-corrected.
	color = Temp;
}
