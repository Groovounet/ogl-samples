#version 120

uniform sampler2D Diffuse;

varying vec2 VertTexcoord;

void main()
{
	gl_FragColor = texture2D(Diffuse, VertTexcoord);
}
