#version 430 core

#define TRANSFORM0	1

layout(binding = TRANSFORM0) uniform transform
{
	mat4 MVP;
} Transform;

struct vertex
{
	vec2 Position;
	vec2 Texcoord;
};

layout(binding = 0) buffer mesh
{
	vertex Vertex[];
} Mesh;

out gl_PerVertex
{
	vec4 gl_Position;
};

out block
{
	vec2 Texcoord;
} Out;

void main()
{	
	int Index = gl_VertexID % Mesh.Vertex.length();

	Out.Texcoord = Mesh.Vertex[gl_VertexID].Texcoord;
	gl_Position = Transform.MVP * vec4(Mesh.Vertex[gl_VertexID].Position, 0.0, 1.0);
}
