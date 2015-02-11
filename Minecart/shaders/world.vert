#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_texture;
//layout(location = 5) in vec3 vertex_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camPosition;

out vec2 uv;
flat out vec3 v_normal;
out vec3 position;
out float v_depth;

void main()
{
	int byte = int(vertex_position.w);
	vec4 verpos = vec4(vertex_position.xyz, 1);

	const int mask = 0x00000003; 
	v_normal.x = float(((byte >> 4) & mask) - 2);
	v_normal.y = float(((byte >> 2) & mask) - 2);
	v_normal.z = float(((byte >> 0) & mask) - 2);
	
    gl_Position = projection * view * model * verpos;
	v_depth = gl_Position.z/100.0;

    position = vec3(model * verpos);
    uv = vertex_texture.xy;
}

