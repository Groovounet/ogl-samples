#version 330 core

#define FRAG_COLOR		0

uniform material
{
	vec4 Diffuse;
} Material;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

void main()
{
	Color = Material.Diffuse;
}
