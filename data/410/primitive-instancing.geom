#version 410 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

layout(triangles, invocations = 6) in;
layout(triangle_strip, max_vertices = 4) out;

layout(location = COLOR) flat in vec3 Color[];
layout(location = COLOR) flat out vec3 GeomColor; // Error on AMD 644431: error(#355) layout location can only set once.

in gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
} gl_in[];

out gl_PerVertex 
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

uniform mat4 MVP;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = MVP * (gl_in[i].gl_Position + vec4(vec2(0.0), - 0.3 + float(0.1) * float(gl_InvocationID), 0.0));
		GeomColor = (vec3(gl_InvocationID + 1) / 6.0 + Color[i]) / 2.0; 
		EmitVertex();
	}
	EndPrimitive();
}

