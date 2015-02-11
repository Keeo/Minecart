#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D sampler;
uniform sampler2D gril;
uniform sampler2D shadow;
uniform vec3 camPosition;

in vec2 uv;
flat in vec3 v_normal;
in vec3 position;
in vec3 light_position;
in float v_depth;

layout(location = 0) out vec4 color;
layout(location = 1) out vec4 nordep;

void main()
{

    color = vec4(texture(gril, uv).rgb * 0.0001 + texture(sampler, uv).rgb, 1);

	nordep.rgb = v_normal;
    nordep.w = v_depth;

}
