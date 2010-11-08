#version 410 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

layout(location = ATTR_POSITION) in vec3 AttrPosition;
out vec3 VertColor;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{	
	gl_Position = vec4(AttrPosition, 1.0);
	VertColor = vec3(1.0, 0.5, 0.0);
}

