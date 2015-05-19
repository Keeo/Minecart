#version 330 core

uniform vec3 lightPosition;

in vec3 vertex_pos;
in vec3 vertex_nor;

out vec3 color;

void main()
{
	color = vec3(1.0,1.0,0.2) / distance(lightPosition, vertex_pos);
}
