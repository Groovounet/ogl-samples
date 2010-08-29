#version 330 core

// Declare all the semantics
#define ATTR_POSITION	0
#define ATTR_COLOR		3
#define ATTR_TEXCOORD	4
#define FRAG_COLOR		0
#define FRAG_RED		0
#define FRAG_GREEN		1
#define FRAG_BLUE		2
#define FRAG_ALPHA		3

uniform mat4 MV;
uniform mat4 MVP;
uniform vec3 Camera;

const vec3 ConstView = vec3(0, 0,-1);
const vec3 ConstNormal = vec3(0, 0, 1);

layout(location = ATTR_POSITION) in vec2 Position;
out vec3 Reflect;

mat3 mat3_cast(mat4 m)
{
	mat3 result;
	result[0][0] = m[0][0]; 
	result[0][1] = m[0][1]; 
	result[0][2] = m[0][2]; 
	result[1][0] = m[1][0]; 
	result[1][1] = m[1][1]; 
	result[1][2] = m[1][2]; 
	result[2][0] = m[2][0]; 
	result[2][1] = m[2][1]; 
	result[2][2] = m[2][2]; 
	return result;
}

void main()
{	
	mat3 MV3x3 = mat3_cast(MV);

	gl_Position = MVP * vec4(Position, 0.0, 1.0);
	vec3 P = MV3x3 * vec3(Position, 0.0);
	vec3 N = MV3x3 * ConstNormal;
	vec3 E = normalize(P - Camera);
	
	Reflect = reflect(E, N);
}
