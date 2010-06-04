#version 330

uniform samplerBuffer Displacement;
flat in int Instance;

void main()
{
	gl_FragColor = texelFetch(Displacement, Instance);
}
