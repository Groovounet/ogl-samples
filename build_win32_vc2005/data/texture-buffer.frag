#version 140

uniform sampler2D Diffuse;
in vec2 VertTexcoord;

void main()
{
	gl_FragColor = texture2D(Diffuse, VertTexcoord);
}
