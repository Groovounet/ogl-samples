#version 330 core

precision highp int;

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0

layout(triangles) in;

flat out int GeomInstance;

uniform mat4 MVP;

void main()
{	
	for(int Layer = 0; Layer < 4; ++Layer)
	{
		gl_Layer = Layer;

		for(int i = 0; i < gl_in.length(); ++i)
		{
			gl_Position = MVP * gl_in[i].gl_Position;
			GeomInstance = Layer;
			EmitVertex();
		}

		EndPrimitive();
	}
}

