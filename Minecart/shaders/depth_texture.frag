#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D sampler;
uniform vec3 camPosition;

in vec2 uv;
flat in vec3 v_normal;
in vec3 position;
in vec3 light_position;

out float color;
in float depth;

void main()
{
	//color.r = depth;
    //color.g = depth * depth;
    color = gl_FragCoord.z;
    //color.g = gl_FragCoord.z * gl_FragCoord.z;
}
