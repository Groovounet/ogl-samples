#version 330 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

in vec4 gl_FragCoord;

uniform sampler3D Diffuse;
uniform mat3 Orientation;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	vec3 SNorm = Orientation * vec3(gl_FragCoord.xy / vec2(640, 480) - 0.5, 0.0);

	Color = texture(Diffuse, SNorm * 0.707106781 + 0.5);
}
