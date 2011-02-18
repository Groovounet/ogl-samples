#version 400 core

layout(location = 0) in vec4 Position;
out vec2 UV;

void main(){	
	gl_Position = Position;
	UV = (Position.xy + vec2(1,1))*0.5;
}

