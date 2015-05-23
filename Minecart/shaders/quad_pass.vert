#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 vertex_position;

uniform vec2 cut = vec2(0);

out vec2  uv;

vec2 offset()
{
	return 2 * cut / vec2(1024, 768);
}

void main()
{
	gl_Position = vec4(vertex_position.xy + offset(), 0.0, 1.0);
	uv = vertex_position.xy * 0.5 + 0.5;
}
