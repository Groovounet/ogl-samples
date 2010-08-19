uniform mat4 MVP;

attribute vec2 Position;

varying vec2 VertTexcoord;

void main()
{	
	VertTexcoord = Position;
	gl_Position = MVP * vec4(Position, 0.0, 1.0);
}