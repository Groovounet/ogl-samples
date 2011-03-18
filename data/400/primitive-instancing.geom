#version 400 core

layout(triangles, invocations = 6) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 VertColor[];
layout(stream = 0) out vec3 GeomColor;

uniform mat4 MVP;

void main()
{	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		GeomColor = (vec3(gl_InvocationID + 1) / 6.0 + VertColor[i]) / 2.0; 
		gl_Position = MVP * (gl_in[i].gl_Position + vec4(vec2(0.0), - 0.3 + float(0.1) * float(gl_InvocationID), 0.0));
		EmitVertex();
	}
	EndPrimitive();
}

