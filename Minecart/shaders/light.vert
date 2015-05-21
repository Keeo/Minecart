#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 vertex_position;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

uniform mat4 lightMat;
out vec3 vertex_pos;
out vec3 v_normal;
out vec4 ShadowCoord;
out float depth;

out vec3 l;
out vec3 n;

vec3 normalUnpack(int byte)
{
	vec3 normal;
	const int mask = 0x00000003; 
	normal.x = -float(((byte >> 4) & mask) - 2);
	normal.y = float(((byte >> 2) & mask) - 2);
	normal.z = -float(((byte >> 0) & mask) - 2);
	return normal;
}

void main()
{
	mat4 MVP = projection * view * model;
	v_normal = normalUnpack(int(vertex_position.w));

    gl_Position = MVP * vec4(vertex_position.xyz, 1);
	//v_normal = (MVP * vec4(v_normal, 1)).xyz;

    vertex_pos = (model * vec4(vertex_position.xyz, 1)).xyz;

	ShadowCoord = lightMat * model * vec4(vertex_position.xyz, 1);

	depth = gl_Position.z/100.0;

	n = ( view * vec4(v_normal, 0) ).xyz;
	l = ( view * vec4(lightPosition, 1 ) - view * vec4(vertex_pos.xyz, 1) ).xyz;
}
