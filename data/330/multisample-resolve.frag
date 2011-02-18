#version 400 core

uniform sampler2DMS t_MS_HDR;
out vec4 color;
in vec2 UV;

vec4 tonemap(vec4 hdr_sample){
	return hdr_sample;
}

vec4 gamma_correct(vec4 aa_ldr_sample){
	return pow(aa_ldr_sample, vec4(1.0/2.2,1.0/2.2,1.0/2.2,1.0/2.2));
}

void main()
{
	// integer UV coordinates, needed for fetching multisampled texture
	ivec2 iUV=ivec2(textureSize(t_MS_HDR)*UV);
	
	// Low range value of the pixel, after box filter
	vec4 aa_ldr_samples = vec4(0,0,0,0);
	
	// For each of the 4 samples
	int samples = 4;
	for (int i=0; i!=samples; i++){
		// The HDR value is the one stored in the texture
		vec4 hdr_sample = texelFetch(t_MS_HDR, iUV, i);
		// The LDR is obtained by applying the tonemapping operator to the HDR value
		vec4 ldr_sample = tonemap(hdr_sample);
		// Box filter (It's a bad one)
		aa_ldr_samples += ldr_sample/=samples;
	}

	// Output color is the resolved value, gamma-corrected.
	color = gamma_correct(aa_ldr_samples);
	color.w = 1;
}