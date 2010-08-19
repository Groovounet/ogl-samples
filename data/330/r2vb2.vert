uniform mat4 MVP;

attribute vec4 Position;
varying vec4 VertColor;

void main()
{	
	VertColor = Position;
	gl_Position = MVP * Position;
}