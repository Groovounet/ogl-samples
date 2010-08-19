uniform sampler2D DiffuseSampler;
varying vec2 VertTexcoord;

void main()
{
	float Height = texture2D(DiffuseSampler, VertTexcoord).x;
	gl_FragColor = vec4(VertTexcoord, Height, 1.0);
}
