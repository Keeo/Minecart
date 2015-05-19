#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 vertex_position;
layout(location = 5) in vec3 vertex_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightMat;
out vec3 vertex_pos;
out vec3 vertex_nor;

void main()
{
    gl_Position = projection * view * model * vec4(vertex_position, 1);
    vertex_pos = (model * vec4(vertex_position, 1)).xyz;
	vertex_nor = vertex_normal.xyz;
}

