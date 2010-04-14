#version 330 core

precision mediump int;
precision highp float;

uniform vec4 Diffuse;

in float VertInstance;

out vec4 Color;

void main()
{
	Color = Diffuse * VertInstance * 0.25;
}
