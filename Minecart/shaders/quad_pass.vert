#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 vertex_position;

uniform vec2 scale = vec2(1);
out vec2  uv;

void main()
{
	gl_Position = vec4(vertex_position.xy * scale, 0.0, 1.0);
	uv = (vertex_position.xy) * 0.5 + 0.5;
}
