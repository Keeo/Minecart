#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D sampler;
uniform vec3 camPosition;

in vec2 uv;
in vec3 v_normal;
in vec3 position;
in vec3 light_position;

out vec4 color;
in float depth;

void main()
{
    vec3 normal = normalize(v_normal);
    color = vec4(normal, depth);
    
}


