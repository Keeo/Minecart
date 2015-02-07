#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D sampler;
uniform sampler2D gril;
uniform vec3 camPosition;

in vec2 uv;
in vec3 v_normal;
in vec3 position;
in vec3 light_position;

out vec3 color;


void main()
{
    //color = vec3(gl_FragCoord.z / 512);
    //color.r = length(camPosition - position) / gl_DepthRange.far;
    //color = vec3(length(position) / gl_DepthRange.far);
    //color = normalize(position);
    color = texture(gril, uv).rgb * texture(sampler, uv).rgb;
    //color = normalize(normalize(texture(sampler, uv).rgb) + normalize(position));
}


