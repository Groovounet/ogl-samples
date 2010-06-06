#version 400

uniform samplerBuffer Diffuse;
flat in int Instance;

void main()
{
	gl_FragColor = texelFetch(Diffuse, Instance);
}
