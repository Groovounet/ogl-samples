#version 410 core

#define POSITION	0
#define COLOR		3
#define TEXCOORD	4
#define FRAG_COLOR	0

layout(location = POSITION) in vec3 Position;
layout(location = COLOR) out vec3 VertColor;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{	
	gl_Position = vec4(Position, 1.0);
	VertColor = vec3(1.0, 0.5, 0.0);
}

